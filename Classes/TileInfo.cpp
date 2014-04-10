//
//  TileInfo.cpp
//  landlord
//
//  Created by Giap Nguyen on 3/10/14.
//
//

#include "TileInfo.h"

TileInfo::TileInfo()
{
  mEdgeTopSts = mEdgeBottomSts = mEdgeLeftSts = mEdgeRightSts = STS_AVAILABLE;
  mNumberEdgeAvailale = NUMBER_EDGE_AVAILABLE;
  mHasBottomPop = mHasLeftPop = mHasRightPop = mHasTopPop = false;
  mHasEdgeTouched = false;
  mGIDTileDown = mGIDTileLeft = mGIDTileRight = mGIDTileUp = -1;
  mGID = 0;
  mBelongToPlayer = 0;
  mHasItem = mHasTree = mHasAxe = mHasStone = false;
}

