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

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
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
        pchMessageStart[0] = 0xc5;
        pchMessageStart[1] = 0xcb;
        pchMessageStart[2] = 0x1a;
        pchMessageStart[3] = 0xae;
        nDefaultPort = 38008;
        nRPCPort = 38009;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // Hashed MainNet Genesis Block Output
        // block.hashMerkleRoot == 988dac66f41fdc30b48ab79a787bd954042b375c7d7ce6a98e33d5f65ce930d0
        // block.nTime = 1530824400
        // block.nNonce = 403743
        // block.GetHash = 00000b4c9b755d17c307bca662aaaee400f06bc84ae8d151ccd441fa965dc191
        //
        const char* pszTimestamp = "SkullCash born Thu, 05 Jul 2018 21:00:00 GMT"; // Sat, 11 Mar 2017 01:28:10 GMT
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1530824400, vin, vout, 0); // Sat, 11 Mar 2017 01:28:10 GMT
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1530824400; // Sat, 11 Mar 2017 01:28:10 GMT
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 403743;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000068a4f0dec3fc356a1dc1ab731ca19d3766223cd715612c31bf956b3d5e6"));
        assert(genesis.hashMerkleRoot == uint256("0x4c605f3f2b3ac1e2a9233399924e41b57b002000d70a41ef7bc66ccadf879c91"));

        //MineGenesis(genesis);

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,63);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,100);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x50)(0xE7)(0xFC)(0x0A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x50)(0x9E)(0x4)(0x2F).convert_to_container<std::vector<unsigned char> >();

        // SkullCash dns seeds
        vSeeds.push_back(CDNSSeedData("seed1.skullcash.tk", "seed1.skullcash.tk"));
        vSeeds.push_back(CDNSSeedData("seed2.skullcash.tk", "seed2.skullcash.tk"));
        vSeeds.push_back(CDNSSeedData("seed3.skullcash.tk", "seed3.skullcash.tk"));
        vSeeds.push_back(CDNSSeedData("seed4.skullcash.tk", "seed4.skullcash.tk"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 125000;
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
        pchMessageStart[0] = 0x79;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0x09;
        pchMessageStart[3] = 0x3b;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        nDefaultPort = 17799;
        nRPCPort = 19977;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1489195700; // Sat, 11 Mar 2017 01:28:20 GMT
        genesis.nNonce = 55;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // Hashed TestNet Genesis Block Output
        // block.hashMerkleRoot == aa86eee12eff9c70d06949ec0185bcfdc08098e59408f41ee2c3063afb9a40da
        // block.nTime = 1489195700
        // block.nNonce = 55
        // block.GetHash = 00357bab563c48a74a593d12a6ea0804a77ae7718cebaf300be6553387681b99
        //

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x00000a10d61633e2655808975dce83c7dd2fe9bcf1537fd1402a981e16d071ed"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,100);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,125);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,41);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x1D)(0x9B)(0x7F)(0x74).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x1D)(0xC0)(0xFC)(0x28).convert_to_container<std::vector<unsigned char> >();

        // SkullCash dns seeds
        // vSeeds.push_back(CDNSSeedData("Seed01",  "0.0.0.0"));
        // vSeeds.push_back(CDNSSeedData("Seed02",  "0.0.0.0"));

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

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
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
