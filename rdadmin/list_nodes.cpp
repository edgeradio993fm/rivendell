// list_nodes.cpp
//
// List Rivendell Livewire Nodes
//
//   (C) Copyright 2002-2018 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <qmessagebox.h>

#include <rd.h>
#include <rddb.h>
#include <rdescape_string.h>
#include <rdpasswd.h>

#include "edit_node.h"
#include "list_nodes.h"
#include "edit_endpoint.h"

ListNodes::ListNodes(RDMatrix *matrix,QWidget *parent)
  : RDDialog(parent)
{
  setModal(true);

  list_matrix=matrix;
  setWindowTitle("RDAdmin - "+tr("Livewire Node List"));

  //
  // Fix the Window Size
  //
  setMinimumSize(sizeHint());

  //
  // Nodes List Box
  //
  list_list_view=new RDListView(this);
  list_list_view->setAllColumnsShowFocus(true);
  list_list_view->setItemMargin(5);
  list_list_view->addColumn(tr("HOSTNAME"));
  list_list_view->setColumnAlignment(0,Qt::AlignLeft);
  list_list_view->addColumn(tr("DESCRIPTION"));
  list_list_view->setColumnAlignment(1,Qt::AlignLeft);
  list_list_view->addColumn(tr("FIRST OUTPUT"));
  list_list_view->setColumnAlignment(2,Qt::AlignLeft);
  list_list_view->addColumn(tr("TCP PORT"));
  list_list_view->setColumnAlignment(3,Qt::AlignCenter);
  connect(list_list_view,
	  SIGNAL(doubleClicked(Q3ListViewItem *,const QPoint &,int)),
	  this,
	  SLOT(doubleClickedData(Q3ListViewItem *,const QPoint &,int)));

  //
  //  Add Button
  //
  list_add_button=new QPushButton(this);
  list_add_button->setFont(buttonFont());
  list_add_button->setText(tr("&Add"));
  connect(list_add_button,SIGNAL(clicked()),this,SLOT(addData()));

  //
  //  Edit Button
  //
  list_edit_button=new QPushButton(this);
  list_edit_button->setFont(buttonFont());
  list_edit_button->setText(tr("&Edit"));
  connect(list_edit_button,SIGNAL(clicked()),this,SLOT(editData()));

  //
  //  Delete Button
  //
  list_delete_button=new QPushButton(this);
  list_delete_button->setFont(buttonFont());
  list_delete_button->setText(tr("&Delete"));
  connect(list_delete_button,SIGNAL(clicked()),this,SLOT(deleteData()));

  //
  //  Close Button
  //
  list_close_button=new QPushButton(this);
  list_close_button->setDefault(true);
  list_close_button->setFont(buttonFont());
  list_close_button->setText(tr("&Close"));
  connect(list_close_button,SIGNAL(clicked()),this,SLOT(closeData()));

  //
  // Load Values
  //
  RefreshList();
}


QSize ListNodes::sizeHint() const
{
  return QSize(400,250);
} 


QSizePolicy ListNodes::sizePolicy() const
{
  return QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


void ListNodes::addData()
{
  RDListViewItem *item;
  int id=-1;
  EditNode *node=new EditNode(&id,list_matrix,this);
  if(node->exec()==0) {
    item=new RDListViewItem(list_list_view);
    item->setId(id);
    RefreshItem(item);
    list_list_view->setSelected(item,true);
    list_list_view->ensureItemVisible(item);
  }
  delete node;
}


void ListNodes::editData()
{
  RDListViewItem *item;

  if((item=(RDListViewItem *)list_list_view->selectedItem())==NULL) {
    return;
  }
  int id=item->id();
  EditNode *node=new EditNode(&id,list_matrix,this);
  if(node->exec()==0) {
    RefreshItem(item);
  }
  delete node;
}


void ListNodes::deleteData()
{
  QString sql;
  RDSqlQuery *q;
  RDListViewItem *item;

  if((item=(RDListViewItem *)list_list_view->selectedItem())==NULL) {
    return;
  }
  if(QMessageBox::question(this,tr("Delete Node"),
			   tr("Are your sure you want to delete this node?"),
			   QMessageBox::Yes,QMessageBox::No)==
     QMessageBox::No) {
    return;
  }
  sql=QString().sprintf("delete from SWITCHER_NODES where ID=%d",item->id());
  q=new RDSqlQuery(sql);
  delete q;
  delete item;
}


void ListNodes::doubleClickedData(Q3ListViewItem *item,const QPoint &pt,
				      int col)
{
  editData();
}


void ListNodes::closeData()
{
  PurgeEndpoints("INPUTS");
  PurgeEndpoints("OUTPUTS");
  done(0);
}


void ListNodes::resizeEvent(QResizeEvent *e)
{
  list_list_view->setGeometry(10,10,size().width()-20,size().height()-80);
  list_add_button->setGeometry(10,size().height()-60,80,50);
  list_edit_button->setGeometry(100,size().height()-60,80,50);
  list_delete_button->setGeometry(190,size().height()-60,80,50);
  list_close_button->setGeometry(size().width()-90,size().height()-60,80,50);
}


void ListNodes::RefreshList()
{
  QString sql;
  RDSqlQuery *q;
  RDListViewItem *item;

  list_list_view->clear();
  sql=QString("select ")+
    "ID,"+
    "HOSTNAME,"+
    "DESCRIPTION,"+
    "BASE_OUTPUT,"+
    "TCP_PORT "+
    "from SWITCHER_NODES where "+
    "(STATION_NAME=\""+RDEscapeString(list_matrix->station())+"\")&&"+
    QString().sprintf("(MATRIX=%d)",list_matrix->matrix());
  q=new RDSqlQuery(sql);
  while(q->next()) {
    item=new RDListViewItem(list_list_view);
    item->setId(q->value(0).toInt());
    item->setText(0,q->value(1).toString());
    item->setText(1,q->value(2).toString());
    if(q->value(3).toInt()==0) {
      item->setText(2,tr("[none]"));
    }
    else {
      item->setText(2,QString().sprintf("%d",q->value(3).toInt()));
    }
    item->setText(3,q->value(4).toString());
  }
  delete q;
}


void ListNodes::RefreshItem(RDListViewItem *item)
{
  QString sql;
  RDSqlQuery *q;

  sql=QString().sprintf("select HOSTNAME,DESCRIPTION,BASE_OUTPUT,TCP_PORT \
                         from SWITCHER_NODES where ID=%d",item->id());
  q=new RDSqlQuery(sql);
  if(q->first()) {
    item->setText(0,q->value(0).toString());
    item->setText(1,q->value(1).toString());
    if(q->value(2).toInt()==0) {
      item->setText(2,tr("[none]"));
    }
    else {
      item->setText(2,QString().sprintf("%d",q->value(2).toInt()));
    }
    item->setText(3,q->value(3).toString());
  }
  delete q;
}


void ListNodes::PurgeEndpoints(const QString &tablename)
{
  QString sql;
  RDSqlQuery *q;

  sql=QString("delete from ")+tablename+" where "+
    "(STATION_NAME=\""+RDEscapeString(list_matrix->station())+"\")&&"+
    QString().sprintf("(MATRIX=%d)&&",list_matrix->matrix());
  RDListViewItem *item=(RDListViewItem *)list_list_view->firstChild();
  while(item!=NULL) {
    sql+=QString("((NODE_HOSTNAME!=\"")+RDEscapeString(item->text(0))+"\")&&"+
      QString().sprintf("(NODE_TCP_PORT!=%d))&&",item->text(3).toInt());
    item=(RDListViewItem *)item->nextSibling();
  }
  sql=sql.left(sql.length()-2);
  q=new RDSqlQuery(sql);
  delete q;
}
