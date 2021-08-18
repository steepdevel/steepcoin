#include <consensus/tx_verify.h>
#include <uint256.h>
#include <map>


typedef std::map<uint256, int> BannedInputs;

const BannedInputs bannedFunds = {
	{
		{ uint256S("0x68b1deb4be4afd0c910fe8bba01c9c38a08b6541c8a55c52f6c06ab82921a945"), 0 },
		{ uint256S("0x039ee929ff2c36d6597bca302c31d1a3ba1042aedee49db940563f0bbccd2eff"), 1 },
		{ uint256S("0x20c8c94be25f866d57b265ba89b7500166f3a2f5aef4845d14839c0643762c6c"), 1 },
		//{ uint256S("0x0c1ae20ee99bc5d7c60c16dbc4ec8547e0a847c0b3c42e24fdabc0a11179bacd"), 1 },
		//{ uint256S("0x4d8b349ca175b24e018885152659c8219270dd0e7b46e388b2da9bb0b0ded418"), 1 },
		{ uint256S("0x1a5d5e5e017ffda8be504e66996fe6e53aace6175fef6615132df72cfdb51a3e"), 1 },
	}
};

bool areBannedInputs(uint256 txid, int vout) {
	for (auto inputs : bannedFunds) {
		if (inputs.first == txid && inputs.second == vout) {
			return true;
		}
	}
	
	return false;
}
