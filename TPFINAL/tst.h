#ifndef TST_H
#define TST_H
#include <iostream>
#include <qstringlist.h>
#include <QDebug>
#include <QFile>


class Tst
{
    private:
      struct node
      {
          int val;
          QChar c;
          node * left;
          node * mid;
          node * right;
      };

      node * root;
      void insertWord(node*&,QString,int,int);
      node * getNode(node*,QString,int) const;
      int getDepth(node*) const;
      bool isFreeNode(node*) const;
      void changeSuccessor(node*&,node*);
      void removeWord(node*&,QString,int,int,bool&);
      void destroy(node*&);
      void getWords(node*, QString, QStringList &) const;
      void printWords(QStringList) const;

    public:
      Tst();
      ~Tst();
      void insert(QString,int&);
      int get(QString) const;
      QStringList getListWords() const;
      bool contains(QString) const;
      int depth() const;
      void remove(QString);
      QStringList prefix(QString) const;
      void uploadFile(int&);
      void saveAllWords() const;
};


#endif // TST_H
