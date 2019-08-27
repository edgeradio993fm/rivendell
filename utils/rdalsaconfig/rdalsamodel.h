// rdalsamodel.h
//
// Abstract an ALSA configuration. 
//
//   (C) Copyright 2009-2018 Fred Gleason <fredg@paravelsystems.com>
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

#ifndef RDALSAMODEL_H
#define RDALSAMODEL_H

#include <QAbstractListModel>
#include <qlist.h>
#include <qstring.h>

#include <rd.h>

#include "rdalsacard.h"

#define START_MARKER "# *** Start of Rivendell configuration generated by rdalsaconfig(1) ***"
#define END_MARKER "# *** End of Rivendell configuration generated by rdalsaconfig(1) ***"

class RDAlsaModel : public QAbstractListModel
{
  Q_OBJECT;
 public:
  RDAlsaModel(unsigned samprate,QObject *parent=0);
  int rowCount(const QModelIndex &parent=QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const;
  QVariant headerData(int section,Qt::Orientation orient,
		      int role=Qt::DisplayRole) const;
  QModelIndex indexOf(const QString &card_id,int pcm_num) const;
  RDAlsaCard *card(const QModelIndex &index) const;
  int pcmNumber(const QModelIndex &index) const;
  bool isEnabled(int row) const;
  void setEnabled(int row,bool state);
  bool loadConfig(const QString &filename);
  bool saveConfig(const QString &filename);

 private:
  void LoadSystemConfig();
  QList<RDAlsaCard *> model_alsa_cards;
  QList<int> model_card_index;
  QList<int> model_pcm_index;
  unsigned model_sample_rate;
  QStringList model_other_lines;
};


#endif  // RDALSAMODEL_H