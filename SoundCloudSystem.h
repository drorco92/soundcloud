//
// Created by user on 07/06/2020.
//

#ifndef SOUNDCLOUD_SOUNDCLOUDSYSTEM_H
#define SOUNDCLOUD_SOUNDCLOUDSYSTEM_H

#endif //SOUNDCLOUD_SOUNDCLOUDSYSTEM_H

#include "library2.h"
#include <string>
#include <assert.h>
#include"Artist.h"
#include "HashTable.h"
#include "List.h"
#include "Song.cpp"
#include "StreamNode.h"


typedef HashTable<Artist> ArtistsHashTable;
class SCS {
public:
    ArtistsHashTable ArtistsTable;
    AvlTree<StreamNode, StreamNodeCompare> allSongsTree;
    SCS();
    ~SCS();
};
StatusType handleError(const std::string& what);
void Recommended(GreatestHitList& HL, int numOfSongs, int*artists, int*songs);

