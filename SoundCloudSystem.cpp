//
// Created by user on 07/06/2020.
//
#include "SoundCloudSystem.h"


void *Init() {
    try{
        SCS* SC = new SCS();
        //SC->ArtistsTable = new ArtistsHashTable();// do we need this?
        //SC->allSongsTree = new AvlTree<StreamNode, StreamNodeCompare>;// do we need this?
        return SC;
    }
    catch(...){
        return nullptr;
    }
}

StatusType AddArtist(void *DS, int artistID) {
    if(!DS||artistID <=0) return INVALID_INPUT;
    try {
        SCS *sys = static_cast<SCS *>(DS);
        if(sys == nullptr) return INVALID_INPUT;
        Artist* new_artist = new Artist(artistID);
        (*sys).ArtistsTable.insert(artistID, new_artist);
        return SUCCESS;
    }
    catch(std::exception& e) {
        std::string what = e.what();
        return handleError(what);
    }
}

StatusType RemoveArtist(void *DS, int artistID) {
    try {
        SCS *sys = static_cast<SCS *>(DS);
        if(sys == nullptr) return INVALID_INPUT;
        Artist &artist = sys->ArtistsTable[artistID];
        if(artist.noSongs() == false) return FAILURE;
        sys->ArtistsTable.remove(artistID);
        return SUCCESS;
    }
    catch(std::exception& e) {
        std::string what = e.what();
        return handleError(what);
    }
}

StatusType AddSong(void *DS, int artistID, int songID) {
    try{
        SCS *sys = static_cast<SCS *>(DS);
        if(sys == nullptr) return  INVALID_INPUT;
        Artist& artist = sys->ArtistsTable[artistID];
        artist.addSong(songID);
        Song* new_song = new Song(songID, 0);// do we need this?
        StreamNode* stream_node = new StreamNode(new_song, artistID);
        sys->allSongsTree.insert(new_song, artistID);
    }
    catch (std::exception& e){
        std::string what = e.what();
        return handleError(what);
    }
}

StatusType RemoveSong(void *DS, int artistID, int songID) {
    try{
        SCS *sys = static_cast<SCS *>(DS);
        if(sys == nullptr) return  INVALID_INPUT;
        Artist& artist = sys->ArtistsTable[artistID];
        int streams = artist.getStreamNum(songID);
        artist.removeSong(songID);
        Song* song = new Song(songID, streams);
        StreamNode* streamNode = new StreamNode(song, artistID);
        sys->allSongsTree.removeElement(streamNode);
        delete streamNode;// do we need this?
    }
    catch (std::exception& e){
        std::string what = e.what();
        return handleError(what);
    }
}

StatusType AddToSongCount(void *DS, int artistID, int songID, int count) {
    try {
        SCS *sys = static_cast<SCS *>(DS);
        if(sys == nullptr || artistID <=0 || songID < 0) return INVALID_INPUT;
        Artist& artist = sys->ArtistsTable[artistID];
        int old_streams = artist.getStreamNum(songID);
        artist.addSongCount(songID);
        int new_streams = old_streams + count;
        Song* old_song = new Song(songID, old_streams);
        Song* new_song = new Song(songID, new_streams);
        StreamNode* old_streamNode = new StreamNode(old_song, artistID);
        StreamNode* new_streamNode = new StreamNode(new_song, artistID);
        sys->allSongsTree.removeElement(old_streamNode);
        delete old_streamNode;
        sys->allSongsTree.insertElement(new_song);
        return SUCCESS;
    }
    catch(std::exception& e) {
        std::string what =e.what();
        return handleError(what);
    }
}

StatusType GetArtistBestSong(void *DS, int artistID, int *songId) {
    try{
        SCS *sys = static_cast<SCS *>(DS);
        Artist& artist = sys->ArtistsTable[artistID];
        *(songId) = artist.getMostStreamed();
    }
    catch(std::exception& e) {
        std::string what =e.what();
        return handleError(what);
    }
}

StatusType GetRecommendedSongInPlace(void *DS, int rank, int *artistId, int *songId) {

    try{
        SCS *sys = static_cast<SCS *>(DS);
        if(sys == nullptr || artistID == nullptr || songID == nullptr || rank <= 0) return INVALID_INPUT;
        Song& song = sys->allSongsTree.findElement()
    }
}