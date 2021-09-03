# Copyright (c) 2013-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

STEEPCOIN_INCLUDES=-I$(builddir) $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

STEEPCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
STEEPCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LIBSTEEPCOIN_SERVER=libsteepcoin_server.a
LIBSTEEPCOIN_COMMON=libsteepcoin_common.a
LIBSTEEPCOIN_CONSENSUS=libsteepcoin_consensus.a
LIBSTEEPCOIN_CLI=libsteepcoin_cli.a
LIBSTEEPCOIN_UTIL=libsteepcoin_util.a
LIBSTEEPCOIN_CRYPTO=crypto/libsteepcoin_crypto.a
LIBSTEEPCOINQT=qt/libsteepcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBSTEEPCOIN_ZMQ=libsteepcoin_zmq.a
endif
if BUILD_STEEPCOIN_LIBS
LIBSTEEPCOINCONSENSUS=libsteepcoinconsensus.la
endif
if ENABLE_WALLET
LIBSTEEPCOIN_WALLET=libsteepcoin_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBSTEEPCOIN_CRYPTO) \
  $(LIBSTEEPCOIN_UTIL) \
  $(LIBSTEEPCOIN_COMMON) \
  $(LIBSTEEPCOIN_CONSENSUS) \
  $(LIBSTEEPCOIN_SERVER) \
  $(LIBSTEEPCOIN_CLI) \
  $(LIBSTEEPCOIN_WALLET) \
  $(LIBSTEEPCOIN_ZMQ)

lib_LTLIBRARIES = $(LIBSTEEPCOINCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_STEEPCOIND
  bin_PROGRAMS += steepcoind
endif

if BUILD_STEEPCOIN_UTILS
  bin_PROGRAMS += steepcoin-cli steepcoin-tx
endif

.PHONY: FORCE check-symbols check-security
# steepcoin core #
STEEPCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  alert.h \
  base58.h \
  bip39.h \
  bip39_english.h \
  bignum.h \
  bech32.h \
  banned.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  policy/policy.h \
  pow.h \
  protocol.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/protocol.h \
  rpc/safemode.h \
  rpc/server.h \
  rpc/register.h \
  rpc/util.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/init.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/walletutil.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
## --- steepoin headers start from this line --- ##
  kernel.h \
  kernelrecord.h

if ENABLE_CHECKPOINTS
  STEEPCOIN_CORE_H += checkpointsync.h
endif


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libsteepcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between steepcoind and steepcoin-qt
libsteepcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(STEEPCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libsteepcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libsteepcoin_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  banned.cpp \
  alert.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  consensus/tx_verify.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/safemode.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  kernel.cpp \
  $(STEEPCOIN_CORE_H)

if ENABLE_CHECKPOINTS
  libsteepcoin_server_a_SOURCES += checkpointsync.cpp
endif

if ENABLE_ZMQ
libsteepcoin_zmq_a_CPPFLAGS = $(STEEPCOIN_INCLUDES) $(ZMQ_CFLAGS)
libsteepcoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libsteepcoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between steepcoind and steepcoin-qt, but only linked
# when wallet enabled
libsteepcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(STEEPCOIN_INCLUDES)
libsteepcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libsteepcoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/init.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  kernelrecord.cpp \
  $(STEEPCOIN_CORE_H)

# crypto primitives library
crypto_libsteepcoin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libsteepcoin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libsteepcoin_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/blake.c \
  crypto/bmw.c \
  crypto/cubehash.c \
  crypto/echo.c \
  crypto/groestl.c \
  crypto/jh.c \
  crypto/keccak.c \
  crypto/luffa.c \
  crypto/shavite.c \
  crypto/simd.c \
  crypto/skein.c \
  crypto/sph_blake.h \
  crypto/sph_bmw.h \
  crypto/sph_cubehash.h \
  crypto/sph_echo.h \
  crypto/sph_groestl.h \
  crypto/sph_jh.h \
  crypto/sph_keccak.h \
  crypto/sph_luffa.h \
  crypto/sph_shavite.h \
  crypto/sph_simd.h \
  crypto/sph_skein.h \
  crypto/sph_types.h

if USE_ASM
crypto_libsteepcoin_crypto_a_SOURCES += crypto/sha256_sse4.cpp
endif

# consensus: shared between all executables that validate any consensus rules.
libsteepcoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(STEEPCOIN_INCLUDES)
libsteepcoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libsteepcoin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  timedatadummy.cpp \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/steepcoinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between steepcoind, and steepcoin-qt and non-server tools
libsteepcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(STEEPCOIN_INCLUDES)
libsteepcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libsteepcoin_common_a_SOURCES = \
  base58.cpp \
  bech32.cpp \
  bip39.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(STEEPCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libsteepcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(STEEPCOIN_INCLUDES)
libsteepcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libsteepcoin_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  random.cpp \
  rpc/protocol.cpp \
  rpc/util.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(STEEPCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libsteepcoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between steepcoin-cli and steepcoin-qt
libsteepcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(STEEPCOIN_INCLUDES)
libsteepcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libsteepcoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(STEEPCOIN_CORE_H)

nodist_libsteepcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# steepcoind binary #
steepcoind_SOURCES = steepcoind.cpp
steepcoind_CPPFLAGS = $(AM_CPPFLAGS) $(STEEPCOIN_INCLUDES)
steepcoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
steepcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
steepcoind_SOURCES += steepcoind-res.rc
endif

steepcoind_LDADD = \
  $(LIBSTEEPCOIN_SERVER) \
  $(LIBSTEEPCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBSTEEPCOIN_UTIL) \
  $(LIBSTEEPCOIN_WALLET) \
  $(LIBSTEEPCOIN_ZMQ) \
  $(LIBSTEEPCOIN_CONSENSUS) \
  $(LIBSTEEPCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

steepcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# steepcoin-cli binary #
steepcoin_cli_SOURCES = steepcoin-cli.cpp
steepcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(STEEPCOIN_INCLUDES) $(EVENT_CFLAGS)
steepcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
steepcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
steepcoin_cli_SOURCES += steepcoin-cli-res.rc
endif

steepcoin_cli_LDADD = \
  $(LIBSTEEPCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBSTEEPCOIN_UTIL) \
  $(LIBSTEEPCOIN_CRYPTO)

steepcoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# steepcoin-tx binary #
steepcoin_tx_SOURCES = \
  steepcoin-tx.cpp \
  timedatadummy.cpp
steepcoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(STEEPCOIN_INCLUDES)
steepcoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
steepcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
steepcoin_tx_SOURCES += steepcoin-tx-res.rc
endif

steepcoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBSTEEPCOIN_COMMON) \
  $(LIBSTEEPCOIN_UTIL) \
  $(LIBSTEEPCOIN_CONSENSUS) \
  $(LIBSTEEPCOIN_CRYPTO) \
  $(LIBSECP256K1)

steepcoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# steepcoinconsensus library #
if BUILD_STEEPCOIN_LIBS
include_HEADERS = script/steepcoinconsensus.h
libsteepcoinconsensus_la_SOURCES = $(crypto_libsteepcoin_crypto_a_SOURCES) $(libsteepcoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libsteepcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libsteepcoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libsteepcoinconsensus_la_LIBADD = $(LIBSECP256K1)
libsteepcoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_STEEPCOIN_INTERNAL
libsteepcoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/steepcoin-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/steepcoin-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/steepcoin-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/steepcoin-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
