/*
 * Fade To Black engine rewrite
 * Copyright (C) 2006-2012 Gregory Montoir (cyx@users.sourceforge.net)
 */

#ifndef RESOURCE_H__
#define RESOURCE_H__

#include "util.h"

enum {
	kResType_SPR,
	kResType_PAL,
	kResType_MAP,
	kResType_ANI,
	kResType_STM,
	kResType_OBJ,
	kResType_SND,
	kResType_F3D,
	kResType_P3D,
	kResTypeCount
};

enum {
	kKeyPathsTableSize = 400,
	kEnvAniDataSize = 38,
	kIniMaxLineLength = 256,
	kLevelDescriptionsCount = 13,
	kSoundKeyPathsTableSize = 10,
	kMusicKeyPathsTableSize = 52,
	kKeyPathNameLength = 96,
	kLevelMusicTableSize = 14
};

struct ResTreeNode {
	int16_t childKey;
	int16_t nextKey;
	uint8_t *data;
	uint32_t dataSize;
	uint32_t dataOffset;
};

struct ResObjectIndex {
	char objectName[64];
	int16_t objectKey;
	uint32_t dataOffs;
};

struct ResKeyPath {
	char pathName[kKeyPathNameLength];
	int16_t key;
};

struct ResLevelDescription {
	char name[16];
	char palKey[kKeyPathNameLength];
	char mapKey[kKeyPathNameLength];
	bool inventory;
	bool map;
	int16_t musicKeys[kLevelMusicTableSize];
};

struct ResMessageDescription {
	const uint8_t *data;
	int16_t frameSync;
	int16_t duration;
	int16_t xPos, yPos;
	int font;
};

struct ResDemoInput {
	int ticks;
	uint16_t key;
	bool pressed;
};

struct Resource {
	ResTreeNode *_treesTable[kResTypeCount];
	uint16_t _treesTableCount[kResTypeCount];
	uint16_t _msgOffsetsTableCount;
	uint16_t *_msgOffsetsTable;
	uint8_t *_msgData;
	uint32_t _cmdOffsetsTableCount;
	uint32_t *_cmdOffsetsTable;
	uint8_t *_cmdData;
	uint32_t _objectIndexesTableCount;
	ResObjectIndex *_objectIndexesTable;
	uint32_t _objectTextDataSize;
	uint8_t *_objectTextData;
	uint16_t _keyPathsTableCount;
	ResKeyPath _keyPathsTable[kKeyPathsTableSize];
	uint32_t _envAniDataCount;
	uint8_t *_envAniData;
	ResLevelDescription _levelDescriptionsTable[kLevelDescriptionsCount];
	char _soundKeyPathsTable[kSoundKeyPathsTableSize][kKeyPathNameLength];
	int16_t _sndKeysTable[kSoundKeyPathsTableSize];
	char _musicKeyPathsTable[kMusicKeyPathsTableSize][kKeyPathNameLength];
	int _demoInputDataSize;
	ResDemoInput *_demoInputData;

	Resource();
	~Resource();

	void loadLevelData(const char *levelName, int levelNum);
	void unload(int type, int16_t key);
	int16_t getPrevious(int type, int16_t key);
	int16_t getNext(int type, int16_t key);
	int16_t getChild(int type, int16_t key);
	int16_t getRoot(int type);
	uint8_t *getEnvAni(int16_t key, int num);
	uint8_t *getData(int type, int16_t key, const char *name);
	void setObjectKey(const char *objectName, int16_t objectKey);
	int getOffsetForObjectKey(int16_t objectKey);
	int16_t getKeyFromPath(const char *path);
	const uint8_t *getCmdData(int num);
	const uint8_t *getMsgData(int num);
	bool getMessageDescription(ResMessageDescription *m, uint32_t value, uint32_t offset);

	void loadINI(FILE *fp, int dataSize);
	void loadCMD(FILE *fp, int dataSize);
	void loadMSG(FILE *fp, int dataSize);
	void loadENV(FILE *fp, int dataSize);
	void loadKeyPaths(FILE *fp, int dataSize);
	void loadObjectIndexes(FILE *fp, int dataSize);
	void loadObjectText(FILE *fp, int dataSize);
	void loadTrigo();
	void loadDEM(FILE *fp, int dataSize);
};

#endif // RESOURCE_H__
