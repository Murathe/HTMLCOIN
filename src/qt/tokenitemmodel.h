#ifndef TOKENITEMMODEL_H
#define TOKENITEMMODEL_H

#include <QAbstractItemModel>

class CWallet;
class WalletModel;
class Token;
struct TokenModelData;

class TokenItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum DataRole{
        Hash = Qt::UserRole + 1,
        AddressRole = Qt::UserRole + 2,
        NameRole = Qt::UserRole + 3,
        SymbolRole = Qt::UserRole + 4,
        DecimalsRole = Qt::UserRole + 5,
        SenderRole = Qt::UserRole + 6,
        BalanceRole = Qt::UserRole + 7,
        RawBalanceRole = Qt::UserRole + 8,
    };

    TokenItemModel(CWallet *wallet, WalletModel *parent = 0);
    ~TokenItemModel();

    /** @name Methods overridden from QAbstractItemModel
        @{*/
    QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    /*@}*/

    Token *getTokenAbi();

public Q_SLOTS:
    void checkTokenBalanceChanged();

private Q_SLOTS:
    void updateToken(const QVariant &token, int status, bool showToken);

private:
    /** Notify listeners that data changed. */
    void emitDataChanged(int index);
    void subscribeToCoreSignals();
    void unsubscribeFromCoreSignals();

    TokenModelData *d;

    friend class TokenItemPriv;
};

#endif // TOKENITEMMODEL_H