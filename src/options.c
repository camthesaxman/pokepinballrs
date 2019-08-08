#include "global.h"
#include "m4a.h"
#include "main.h"

void OptionsMain(void)
{
    gUnknown_08527F08[gMain.subState]();
}

extern const u16 gUnknown_0852B468[];
extern const u8 gUnknown_08528828[];
extern const u8 gUnknown_0852A848[];
extern const u8 gUnknown_08528028[];
extern const u8 gUnknown_0852A048[];

void sub_51240(void)
{
    sub_438();

    REG_DISPCNT = 0x1080;
    REG_BG0CNT = 4;
    REG_DISPCNT |= 0x100;
    REG_BG1CNT = 0x109;
    REG_DISPCNT |= 0x200;

    gMain.unk16 = REG_DISPCNT;

    DmaCopy16(3, gUnknown_0852B468, (void *)PLTT, 0x200);
    DmaCopy16(3, gUnknown_08528828, (void *)(VRAM + 0x4000), 0x1800);
    DmaCopy16(3, gUnknown_0852A848, (void *)(VRAM + 0x8000), 0xC00);
    DmaCopy16(3, gUnknown_08528028, gUnknown_03005C00, 0x800);
    DmaCopy16(3, gUnknown_03005C00, (void *)VRAM, 0x800);

    if (gGameBoyPlayerEnabled != 1)
    {
         sub_1068C(0x12, 4, 2, 1, 2);
         sub_1068C(0x12, 5, 3, 2, 2);
    }

    DmaCopy16(3, gUnknown_03005C00, (void *)VRAM, 0x800);
    DmaCopy16(3, gUnknown_0852A048, (void *)(VRAM + 0x800), 0x800);
    DmaCopy16(3, gGBAButtonIcons_Pals, (void *)(PLTT + 0x200), 0x60);
    DmaCopy16(3, gOptionsSprites_Gfx, (void *)(VRAM + 0x10000), 0x2020);
	sub_513B8();
	sub_51C9C();
	m4aMPlayAllStop();
	sub_CBC();
	sub_24C();
	sub_10C0();

    gMain.subState++;
}

struct UnknownStruct1
{
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u16 unk18;
    u8 unk1A[6];
    u16 unk20;
    u16 unk22;
    u16 unk24[2];
    u16 unk28;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
};

extern struct UnknownStruct1 gUnknown_02002920;

// This is probably permanently saved data like pokedex and high scores.
struct SaveData
{
    /*0x74*/ u8 pokedexFlags[204];
    /*0x140*/ u8 filler140[1];
    /*0x141*/ u8 unk141;
    /*0x142*/ u8 unk142;
    /*0x143*/ u8 unk143;
    /*0x144*/ u8 filler144[0x2D8-0x144];
              s8 signature[10];
              u16 unk2E2;
              u32 unk2E4;
};
extern struct SaveData gUnknown_0200B134_;

#define gUnknown_0200B134 gUnknown_0200B134_
asm(".set gUnknown_0200B134_, gUnknown_0200B134");

extern u8 gUnknown_02031AF0[][10];
extern u8 gUnknown_08527ED6[][10];

void sub_513B8(void)
{
    int i;
    int j;

    gUnknown_02002920.unk0 = 0;
    gUnknown_02002920.unk2 = 0;
    gUnknown_02002920.unk4 = 0;
    gUnknown_02002920.unk6 = 1;
    gUnknown_02002920.unk8 = 0;
    gUnknown_02002920.unkA = 0;
    gUnknown_02002920.unkC = gUnknown_0200B134.unk143;
    gUnknown_02002920.unkE = 0;
    gUnknown_02002920.unk10 = 0;
    gUnknown_02002920.unk12 = 0;
    gUnknown_02002920.unk13 = 0;
    gUnknown_02002920.unk14 = 1;
    gUnknown_02002920.unk15 = 0;
    gUnknown_02002920.unk16 = 0;
    gUnknown_02002920.unk17 = 1;
    gUnknown_02002920.unk18 = 0;
    for (i = 0; i < 6; i++)
        gUnknown_02002920.unk1A[i] = 0;
    gUnknown_02002920.unk20 = 0;
    gUnknown_02002920.unk22 = 0;
    for (i = 0; i < 2; i++)
        gUnknown_02002920.unk24[i] = 10;
    gUnknown_02002920.unk28 = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 10; j++)
            gUnknown_02031AF0[i][j] = gUnknown_08527ED6[i][j];
    }
    sub_52528();
    if (gGameBoyPlayerEnabled == 1)
    {
        gUnknown_02002920.unk2A = gUnknown_0200B134.unk141;
        gUnknown_0200B134.unk141 = 1;
    }
    else
    {
        gUnknown_02002920.unk2A = 0;
        gUnknown_0200B134.unk141 = 0;
    }
    gUnknown_02002920.unk2E = 0;
    gUnknown_02002920.unk2B = 0;
    gUnknown_02002920.unk2C = 0;
    gUnknown_02002920.unk2D = 0;
    gUnknown_02002920.unk2F = 0;
    gUnknown_02002920.unk30 = 0;
}
