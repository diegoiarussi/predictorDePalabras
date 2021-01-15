#include "tst.h"


Tst::Tst()
{
    root = NULL;
}


void Tst::destroy(node *& x)
{
    if (x != NULL)
    {
        destroy(x->left);
        destroy(x->mid);
        destroy(x->right);
        delete x;
        x = NULL;
    }
}


Tst::~Tst()
{
    destroy(root);
}


void Tst::insertWord(node *& x, QString key, int val, int d)
{
    QChar c = key[d];
    if (x == NULL){
        x = new node();
        x->c = c;
    }
    if (c < x->c)
        insertWord(x->left,key,val,d);
    else
        if (c > x->c)
            insertWord(x->right,key,val,d);
        else
            if (d < (key.length() - 1))
                insertWord(x->mid,key,val,d+1);
            else
                x->val = val;
}


void Tst::insert(QString key, int & val)
{
    insertWord(root,key,val,0);
    val++;
}


Tst::node * Tst::getNode(node * x, QString key, int d) const
{
    if (x == NULL)
        return NULL;
    QChar c = key[d];
    if (c < x->c)
        return getNode(x->left,key,d);
    else
    {
        if (c > x->c)
            return getNode(x->right,key,d);
        else
        {
            if (d < (key.length() - 1))
                return getNode(x->mid,key,d+1);
            else
                return x;
        }
    }
}


int Tst::get(QString key) const
{
    node * x = getNode(root,key,0);
    if (x == NULL)
        return 0;
    return x->val;
}


bool Tst::contains(QString key) const
{
    node * x = getNode(root,key,0);
    if (x == NULL)
        return false;
    return true;
}


int Tst::getDepth(node * x) const
{
    if (x != NULL)
    {
        int right = getDepth(x->right);
        int mid = getDepth(x->mid);
        int left = getDepth(x->left);
        if ((right >= mid) && (right >= left))
            return (right +1);
        else
        {
            if ((mid >= right) && (mid >= left))
                return (mid +1);
            else
                return (left +1);
        }
    }
    else
        return 0;
}


int Tst::depth() const
{
    return getDepth(root);
}


bool Tst::isFreeNode(node * x) const
{
    if ((!x->left) && (!x->mid) && (!x->right))
        return true;
    return false;
}


void Tst::changeSuccessor(node *& x, node * aux)
{
    if (x->right != NULL)
        changeSuccessor(x->right, aux);
    else
        x->right = aux->right;
}


void Tst::removeWord(node *& x, QString key, int d, int v, bool & check)
{
    if (x == NULL)
        return;
    QChar c = key[d];
    if (c < x->c)
        removeWord(x->left,key,d,v,check);
    else
    {
        if (c > x->c)
            removeWord(x->right,key,d,v,check);
        else
        {
            if (d < (key.length() - 1))
                removeWord(x->mid,key,d+1,v,check);
            else
                v = x->val;
        }
    }

    if (!check)
    {
        if (x->c == key[d])
        {
            if (x->val == v || x->val == 0)
            {
                if (isFreeNode(x))
                {
                    node * aux = new node();
                    aux = x;
                    x = NULL;
                    delete aux;
                }
                else
                {
                    if (!x->mid)
                    {
                        if (x->left != NULL)
                        {
                            node * aux = new node();
                            aux = x;
                            x = x->left;
                            changeSuccessor(x,aux);
                            delete aux;
                        }
                        else
                        {
                            node * aux = new node();
                            aux = x;
                            x = x->right;
                            delete aux;
                        }
                    }
                    else
                        x->val = 0;
                }
            }
        }
        else
            check = true;
    }
}


void Tst::remove(QString key)
{
    int v = -1;
    bool check = false;
    removeWord(root,key,0,v,check);
}


void Tst::getWords(node *x, QString key, QStringList & q) const
{
    if (x != NULL)
    {
        key += x->c;
        if (x->val != 0)
            q.append(key);
        getWords(x->mid,key,q);
        key = key.remove(key.size()-1, 1);
        getWords(x->left,key,q);
        getWords(x->right,key,q);
    }
    else
        return;
}


void Tst::printWords(QStringList q) const
{
    QString key;
    while (!q.empty())
    {
        key = q.front();
        qDebug() << key << '\n';
        q.pop_front();
    }
}


QStringList Tst::prefix(QString prefix) const
{
    node * x = getNode(root,prefix,0);
    QStringList q;
    QString key = prefix;
    if (x->val != 0)
        q.append(prefix);
    getWords(x->mid,key,q);
    return q;
}


void Tst::uploadFile(int & val)
{
    QFile file("/Users/diegoiarussi/words.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        insert(line,val);
        val++;
    }
    file.close();
}


void Tst::saveAllWords() const
{
    QStringList q;
    getWords(root,"",q);
    QFile file("/Users/diegoiarussi/result.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    while (!q.empty())
    {
        out << q.front() << '\n';
        q.pop_front();
    }
    file.close();
}


QStringList Tst::getListWords() const
{
    QStringList q;
    getWords(root,"",q);
    return q;
}
