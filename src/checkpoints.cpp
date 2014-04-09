// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of 
        (      0, uint256("0x3d9e5080e63c65fb2dd117ea0330892e450c15b5a59c1a6c4e3fb2a01f16d0db"))
	(      1, uint256("0xaf7f1e670b61d341202dec0e873b079eeabd0b745c91d64a799108e61a4c97c9"))
	(    100, uint256("0x2518c68fb48de031618aef649b969efa4adcadaa6d1673ae0153b657b2b1f14b"))
	(    500, uint256("0x8849fb42e5144e72625b3b4ca2d68ca0c47aaa3ffb4772342bebbb17074f7858"))
	(   1000, uint256("0x3abf5fa6f0721e6d85085a3f946d62a2d659595d50243fde1aea8cec590f1534")) // End of 2x reward
	(   2000, uint256("0x93d7a286fdeef28898449e7bc6381d67e74e82035bea071944a2156d32adbd8e"))
	(   3000, uint256("0x0a5b9cda20f4cfd10fd190324e80972eba7181d2f7fc4c21a6b608a32b0efc59"))
	(   4000, uint256("0x0057269b472fdcba904e9e7f47b464e6df9a07de9be32319298a378547c81608"))
	(   5000, uint256("0x67aba0ac58cbd551640406e4a20d9b1aa406797608d7877a4df3e25257350a5c"))
	(  10000, uint256("0x67a9e44519d227df5b88b1e413600154f204cc32e22ecb2398ec8031014c3644"))
	(  50000, uint256("0x25a40fb0747dcca9ba4c3b0a599e8cf70ba1c63638b48e9b45624f565c93ce75"))
	(  75000, uint256("0x85e1f688f7926959e18de31532dc72cd7b391c2a2748fd6d4ada4c9293d101be"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
