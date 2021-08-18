Shared Libraries
================

## steepcoinconsensus

The purpose of this library is to make the verification functionality that is critical to Steepcoin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `steepcoinconsensus.h` located in  `src/script/steepcoinconsensus.h`.

#### Version

`steepcoinconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`steepcoinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `steepcoinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `steepcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `steepcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/steepcoin/bips/blob/master/bip-0016.mediawiki)) subscripts
- `steepcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/steepcoin/bips/blob/master/bip-0066.mediawiki)) compliance
- `steepcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/steepcoin/bips/blob/master/bip-0147.mediawiki))
- `steepcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/steepcoin/bips/blob/master/bip-0065.mediawiki))
- `steepcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/steepcoin/bips/blob/master/bip-0112.mediawiki))
- `steepcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/steepcoin/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `steepcoinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `steepcoinconsensus_verify_script` for the verification status)*
- `steepcoinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `steepcoinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `steepcoinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `steepcoinconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NSteepCoin](https://github.com/NicolasDorier/NSteepCoin/blob/master/NSteepCoin/Script.cs#L814) (.NET Bindings)
- [node-libsteepcoinconsensus](https://github.com/bitpay/node-libsteepcoinconsensus) (Node.js Bindings)
- [java-libsteepcoinconsensus](https://github.com/dexX7/java-libsteepcoinconsensus) (Java Bindings)
- [steepcoinconsensus-php](https://github.com/Bit-Wasp/steepcoinconsensus-php) (PHP Bindings)
