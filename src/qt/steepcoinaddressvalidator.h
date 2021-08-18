// Copyright (c) 2011-2014 The SteepCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef STEEPCOIN_QT_STEEPCOINADDRESSVALIDATOR_H
#define STEEPCOIN_QT_STEEPCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class SteepCoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SteepCoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** SteepCoin address widget validator, checks for a valid steepcoin address.
 */
class SteepCoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SteepCoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // STEEPCOIN_QT_STEEPCOINADDRESSVALIDATOR_H
