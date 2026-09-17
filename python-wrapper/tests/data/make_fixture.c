/* Writes test_ramp.gwf, the fixture test_04_frame_io.py reads: one channel
 * named RAMP carrying i = 0, 1, 2, ... so a test can assert every sample.
 *
 *   cc make_fixture.c -o make_fixture -lframel -lm && ./make_fixture
 */
#include <stdio.h>
#include "FrameL.h"

#define FS 16.0     /* Hz -- small enough to keep the fixture a few kB */
#define NDATA 64    /* 4 s in one frame */
#define GPS 700000000

int main(void)
{
    FrameH *frame;
    FrAdcData *adc;
    FrFile *oFile;
    int i;

    FrLibSetLvl(0);

    frame = FrameHNew("p4TSA-test");
    frame->GTimeS = GPS;
    frame->GTimeN = 0;
    frame->dt = NDATA / FS;

    adc = FrAdcDataNew(frame, "RAMP", FS, NDATA, -64);
    for (i = 0; i < NDATA; i++)
        adc->data->dataD[i] = (double) i;

    oFile = FrFileONew("test_ramp.gwf", 0);
    if (oFile == NULL) {
        fprintf(stderr, "cannot open output file: %s\n", FrErrorGetHistory());
        return 1;
    }
    if (FrameWrite(frame, oFile) != FR_OK) {
        fprintf(stderr, "cannot write frame: %s\n", FrErrorGetHistory());
        return 1;
    }
    FrFileOEnd(oFile);
    FrameFree(frame);

    printf("wrote test_ramp.gwf: channel RAMP, %d samples at %g Hz from GPS %d\n",
           NDATA, FS, GPS);
    return 0;
}
