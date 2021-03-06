/*
 * Fade To Black engine rewrite
 * Copyright (C) 2006-2012 Gregory Montoir (cyx@users.sourceforge.net)
 */

#ifndef RENDER_H__
#define RENDER_H__

#include "util.h"

enum {
	kFlatColorRed = 512,
	kFlatColorGreen,
	kFlatColorYellow,
	kFlatColorBlue,
	kFlatColorShadow,
	kFlatColorLight,
	kFlatColorLight9
};

struct Texture;

struct Render {
	uint8_t _clut[256 * 3];
	float _pixelColorMap[4][256];
	int _w, _h;
	struct {
		uint8_t *buf;
		Texture *tex;
		bool hflip;
		int r, g, b;
	} _overlay;
	struct {
		bool changed;
		int pw;
		int ph;
	} _viewport;

	Render();
	~Render();

	void flushCachedTextures();

	void setCameraPos(int x, int y, int z, int shift = 0);
	void setCameraPitch(int a);

	void drawPolygonFlat(const Vertex *vertices, int verticesCount, int color);
	void drawPolygonTexture(const Vertex *vertices, int verticesCount, int primitive, const uint8_t *texData, int texW, int texH, int16_t texKey);
	void drawParticle(const Vertex *pos, int color);
	void drawSprite(int x, int y, const uint8_t *texData, int texW, int texH, int16_t texKey);
	void drawRectangle(int x, int y, int w, int h, int color);

	void beginObjectDraw(int x, int y, int z, int ry, int shift = 0);
	void endObjectDraw();

	void updateFrustrumPlanes();
	bool isQuadInFrustrum(const Vertex *vertices, int verticesCount);
	bool isBoxInFrustrum(const Vertex *vertices, int verticesCount);

	void setOverlayBlendColor(int r, int g, int b);
	void setOverlayDim(int w, int h, bool hflip = false);
	void copyToOverlay(int x, int y, const uint8_t *data, int pitch, int w, int h, int transparentColor = -1);

	void setPalette(const uint8_t *pal, int count);
	void clearScreen();
	void setupProjection(int mode = 0);
	void setupProjection2d();
	void drawOverlay();
	void resizeScreen(int w, int h);
};

#endif // RENDER_H__
