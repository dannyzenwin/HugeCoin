// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
	uint8_t addr[16];
	uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
	// It'll only connect to one or two seed nodes because once it connects,
	// it'll get a pile of addresses with newer timestamps.
	// Seed nodes are given a random 'last seen time' of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int k = 0; k < count; ++k)
	{
		struct in_addr ip;
		unsigned int i = data[k], t;

		// -- convert to big endian
		t = (i & 0x000000ff) << 24u
			| (i & 0x0000ff00) << 8u
			| (i & 0x00ff0000) >> 8u
			| (i & 0xff000000) >> 24u;

		memcpy(&ip, &t, sizeof(ip));

		CAddress addr(CService(ip, port));
		addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
		vSeedsOut.push_back(addr);
	}
}

class CMainParams : public CChainParams {
public:
	CMainParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0xb6;
		pchMessageStart[1] = 0xbc;
		pchMessageStart[2] = 0xa6;
		pchMessageStart[3] = 0xa8;
		vAlertPubKey = ParseHex("041f5288d86851bd87373ac64d5c4c68843773827d6938c3deb416c0ca7ea4fd25323bb8d141f77bd0d3a46c8efa8773f0bff48f7ee60f64540585cbb65494c9e1");
		nDefaultPort = 15888;
		nRPCPort = 15889;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

		// Build the genesis block. Note that the output of the genesis coinbase cannot
		// be spent as it did not originally exist in the database.
		//
		//CBlock(hash=0000ebc8051bff80f7946f4420efb219e66f66b89fdc1df0ed8a30b428bf0033, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
		//  Coinbase(hash=59589791e1, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
		//    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
		//    CTxOut(empty)
		//  vMerkleTree: 59589791e1
		const char* pszTimestamp = "Hugecoin join now!";
		std::vector<CTxIn> vin;
		vin.resize(1);
		vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		std::vector<CTxOut> vout;
		vout.resize(1);
		vout[0].SetEmpty();
		vout[0].nValue = 5;
		CTransaction txNew(1, 1511883688, vin, vout, 0);


		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1511883888;
		genesis.nBits = 520159231;
		genesis.nNonce = 110;

		hashGenesisBlock = genesis.GetHash();


		assert(genesis.hashMerkleRoot == uint256("0xac6ce58aed1669dace030e14dc5e5f2bdc85bd9bb62aab4f58e2d1c2a3c06f4b"));
		assert(hashGenesisBlock == uint256("0xbb2e59197319e3736d7c2e679a729243099843bdee873c407b41c544874578b9"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 88);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 158);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xC2)(0x3E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xB4).convert_to_container<std::vector<unsigned char> >();

		vSeeds.push_back(CDNSSeedData("0", "35.196.127.156"));
		vSeeds.push_back(CDNSSeedData("1", "130.211.52.40"));
		vSeeds.push_back(CDNSSeedData("2", "35.240.201.117"));
		convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

		nPoolMaxTransactions = 3;

		
		strDarksendPoolDummyAddress = "HNZhGtxQpoLVcnhpRSbEuPF3eqyLMDVsfJ";
		nLastPOWBlock = 2012;
		nPOSStartBlock = 1500;
	}


	virtual const CBlock& GenesisBlock() const { return genesis; }
	virtual Network NetworkID() const { return CChainParams::MAIN; }

	virtual const vector<CAddress>& FixedSeeds() const {
		return vFixedSeeds;
	}
protected:
	CBlock genesis;
	vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
	CTestNetParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x1c;
		pchMessageStart[1] = 0x2e;
		pchMessageStart[2] = 0xa6;
		pchMessageStart[3] = 0xc8;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		vAlertPubKey = ParseHex("041f5288d86851bd87373ac64d5c4c68843773827d6938c3deb416c0ca7ea4fd25323bb8d141f77bd0d3a46c8efa8773f0bff48f7ee60f64540585cbb65494c9e1");
		nDefaultPort = 20114;
		nRPCPort = 20115;
		strDataDir = "testnet";

		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nBits = 520159231;
		genesis.nNonce = 1028;

		assert(hashGenesisBlock == uint256("0xbb2e59197319e3736d7c2e679a729243099843bdee873c407b41c544874578b9"));

		vFixedSeeds.clear();
		vSeeds.clear();

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 11);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x88)(0xBC).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x82)(0x88).convert_to_container<std::vector<unsigned char> >();

		convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

		nLastPOWBlock = 0x7fffffff;
	}
	virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
	return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
	switch (network) {
	case CChainParams::MAIN:
		pCurrentParams = &mainParams;
		break;
	case CChainParams::TESTNET:
		pCurrentParams = &testNetParams;
		break;
	default:
		assert(false && "Unimplemented network");
		return;
	}
}

bool SelectParamsFromCommandLine() {

	bool fTestNet = GetBoolArg("-testnet", false);

	if (fTestNet) {
		SelectParams(CChainParams::TESTNET);
	}
	else {
		SelectParams(CChainParams::MAIN);
	}
	return true;
}
