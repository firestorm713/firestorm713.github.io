int Dimensions = 256; // Size of the Texture
float basePersistance = 0.5f;
SDL_Surface* Octaves[Log2(Dimensions)];
for(i in Octaves)
{
	int Stride = Octaves[i]/pow(2, i);
	int numDataPoints = 2*(pow(Dimensions, 2)/pow(Stride, 2))+1;
	dColor CurOctave[numDataPoints];
	float amplitude = pow(basePersistance, i);
	for(int j in CurOctave)
	{
		CurOctave[j].r = rand()*amplitude;
		CurOctave[j].g = rand()*amplitude;
		CurOctave[j].b = rand()*amplitude;
		CurOctave[j].a = 255;
	}
	
	// 0-1, 1-2; 2-3, 3-4, 4-5; 6-7, 7-8, 8-9;
	// 0-1, 1-2, 2-3, 3-4,
	int y;
	int OctIndex = 0;
	for(y = 0; y < Dimensions; y+=stride)
	{
		for(int xOffset = 0; xOffset < Dimensions; xOffset+=stride)
		{
			for(int x = 0; x < stride; x++)
			{
				float percentage = (float)x/(float)stride;
				Uint32 from = SDL_MapRGBA(fmt, CurOctave[OctIndex].r, CurOctave[OctIndex].g, CurOctave[OctIndex].b, CurOctave[OctIndex].a);
				Uint32 to = SDL_MapRGBA(fmt, CurOctave[OctIndex+1].r, CurOctave[OctIndex+1].g, CurOctave[OctIndex+1].b, CurOctave[OctIndex+1].a);
				Uint32 interpedColor = coserpColor(windowSurface, from, to percentage);
			}
			OctIndex++;
		}
		if((y+stride)==Dimensions)
			y--;
		OctIndex++;
	}
}