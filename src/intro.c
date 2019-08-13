#include "global.h"
#include "m4a.h"
#include "main.h"
#include "titlescreen.h"

extern void (*const gUnknown_080792CC[])(void);
extern const u8 gUnknown_080798C0[];
extern s16 gUnknown_0202BF10;
extern s8 gUnknown_0202C790;

extern u8 gIntroCopyright_Gfx[];
extern u16 gIntroCopyright_Pal[];
extern void (*const gUnknown_080792E0[])(void);

extern void sub_FF74();
extern void sub_93F8(void);

void IntroMain(void)
{
    gUnknown_080792CC[gMain.subState]();
}

void sub_929C(void)
{
    ResetSomeGraphicsRelatedStuff();

    REG_DISPCNT = 0x80;
    REG_BG1CNT = 5;
    REG_DISPCNT |= 0x200;

    DmaCopy16(3, gUnknown_080798C0, (void *)(VRAM), 0x800);
    DmaCopy16(3, gIntroCopyright_Gfx, (void *)(VRAM + 0x4000), 0x800);
    DmaCopy16(3, gIntroCopyright_Pal, (void *)(PLTT), 0x200);
    gMain.unk16 = REG_DISPCNT;

    gUnknown_0202BF10 = 0;
    gUnknown_0202C790 = 0;
    SetMainCallback(sub_93F8);
    sub_CBC();
    sub_24C();
    gMain.subState++;
}

#ifdef NONMATCHING
// Same push {lr} bullshit. We probably have the wrong compiler version.
void sub_9348(void)
{
    if (++gUnknown_0202BF10 > 0x78)
    {
        gUnknown_0202BF10 = 0;
        gMain.subState++;
    }
}
#else
NAKED
void sub_9348(void)
{
    asm_unified("\n\
	ldr r1, _08009368 @ =gUnknown_0202BF10\n\
	ldrh r0, [r1]\n\
	adds r0, #1\n\
	strh r0, [r1]\n\
	lsls r0, r0, #0x10\n\
	asrs r0, r0, #0x10\n\
	cmp r0, #0x78\n\
	ble _08009364\n\
	movs r0, #0\n\
	strh r0, [r1]\n\
	ldr r1, _0800936C @ =gMain\n\
	ldrb r0, [r1, #3]\n\
	adds r0, #1\n\
	strb r0, [r1, #3]\n\
_08009364:\n\
	bx lr\n\
	.align 2, 0\n\
_08009368: .4byte gUnknown_0202BF10\n\
_0800936C: .4byte gMain\n");
}
#endif

void sub_9370(void)
{
    sub_FF74(0);
    sub_D10();
    gMain.subState++;
}

void sub_938C(void)
{
    gUnknown_080792E0[gUnknown_0202C790]();
    gUnknown_0202BF10++;
    if (gMain.newKeys & 9)
        gMain.subState = 4;
}

void sub_93D0(void)
{
    sub_2B4();
    m4aMPlayAllStop();
    sub_D10();
    ResetMainCallback();
    gAutoDisplayTitlescreenMenu = 0;
    SetMainGameState(STATE_TITLE);
}

void sub_93F8(void)
{
    if (REG_DISPSTAT & 8)
    {
        m4aSoundMain();
        VBlankIntrWait();
        DmaCopy32(3, gOamBuffer, (void *)OAM, 0x400);

        REG_DISPCNT = gMain.unk16;

        REG_BG0HOFS = gMain.unk2E8[0].unk0;
        REG_BG0VOFS = gMain.unk2E8[0].unk2;

        REG_BG1HOFS = gMain.unk2E8[1].unk0;
        REG_BG1VOFS = gMain.unk2E8[1].unk2;

        REG_BG2HOFS = gMain.unk2E8[2].unk0;
        REG_BG2VOFS = gMain.unk2E8[2].unk2;

        REG_BG3HOFS = gMain.unk2E8[3].unk0;
        REG_BG3VOFS = gMain.unk2E8[3].unk2;
    }
}

struct IntroData
{
    u16 unk0;
    u16 unk2;
    u8 filler4[4];
    s16 unk8;
    s16 unkA;
    u16 unkC;
    u16 unkE;
    u8 filler10[4];
    u16 unk14;
    u8 filler16[2];
    u16 unk18;
    u16 unk1A;
    u8 filler1C[8];
    u16 unk24;
    u16 unk26;
    u8 filler28[4];
    u16 unk2C;
};

extern struct IntroData gUnknown_0202ADA0;

extern u8 gUnknown_080B9CC0[];
extern u8 gUnknown_080BC4C0[];
extern u8 gUnknown_080BB4C0[];
extern u8 gUnknown_080B3CA0[];
extern u8 gUnknown_080B44A0[];
extern u8 gUnknown_080BD4C0[];
extern u16 gIntroScene1Sprites_Pals[];
extern u8 gIntroScene1Sprites_Gfx[];
extern u8 gUnknown_0201C1C0[];

extern void sub_10170(void *, void *, int, u16);
extern void sub_96A8(void);
extern void sub_FEB8();

void sub_9498(void)
{
    ClearGraphicsMemory();
    sub_518();
    ClearSprites();

    REG_DISPCNT = 0x1000;

    REG_BG0CNT = 0x1A00;
    REG_DISPCNT |= 0x100;

    REG_BG1CNT = 0x5B01;
    REG_DISPCNT |= 0x200;

    REG_BG2CNT = 0x5D02;
    REG_DISPCNT |= 0x400;

    REG_BG3CNT = 0x1F03;
    REG_DISPCNT |= 0x800;

    DmaCopy16(3, gUnknown_080B9CC0, (void *)(VRAM + 0xD000), 0x800);
    DmaCopy16(3, gUnknown_080BC4C0, (void *)(VRAM + 0xD800), 0x1000);
    DmaCopy16(3, gUnknown_080BB4C0, (void *)(VRAM + 0xE800), 0x1000);
    DmaCopy16(3, gUnknown_080B3CA0, (void *)(VRAM + 0xF800), 0x800);
    DmaCopy16(3, gUnknown_080B44A0, (void *)(VRAM), 0x5800);
    DmaCopy16(3, gUnknown_080BD4C0, gUnknown_0201C1C0, 0x6800);
    sub_10170(gIntroScene1Sprites_Pals, (void *)(PLTT), 0x200, 0x20);

    DmaCopy16(3, gIntroScene1Sprites_Gfx, (void *)(VRAM + 0x10000), 0x8000);
    DmaCopy16(3, gIntroScene1Sprites_Pals, (void *)(PLTT + 0x200), 0x200);
    sub_96A8();

    gMain.unk2E8[0].unk0 = gUnknown_0202ADA0.unk0;
    gMain.unk2E8[0].unk2 = gUnknown_0202ADA0.unk2;

    gMain.unk2E8[1].unk0 = gUnknown_0202ADA0.unk24;
    gMain.unk2E8[1].unk2 = gUnknown_0202ADA0.unk26;

    gMain.unk2E8[2].unk0 = gUnknown_0202ADA0.unkC;
    gMain.unk2E8[2].unk2 = gUnknown_0202ADA0.unkE;

    gMain.unk2E8[3].unk0 = gUnknown_0202ADA0.unk18;
    gMain.unk2E8[3].unk2 = gUnknown_0202ADA0.unk1A;

    sub_CBC();
    sub_FEB8((void *)(PLTT), gIntroScene1Sprites_Pals, 0);

    DmaCopy16(3, gIntroScene1Sprites_Pals, (void *)(PLTT + 0x200), 0x200);
    DmaCopy16(3, NULL, (void *)(PLTT + 0x200), 0x20);
    gUnknown_0202C790++;
}

struct IntroData2
{
    u16 unk0;
    u16 unk2;
    u8 filler4[4];
    s16 unk8;
    s16 unkA;
    u8 unkC;
    u8 fillerD[3];
    u16 unk10;
    u16 unk12;
    u8 filler14[4];
    u16 unk18;
    u8 filler1A[2];
    u8 unk1C;
    u8 filler1D[3];
    u16 unk20;
    u16 unk22;
    u8 filler24[8];
    u8 unk2C;
    u8 filler2D[3];
    u16 unk30;
    u16 unk32;
    u8 filler34[6];
    u16 unk3A;
    u8 unk3C;
    u8 filler3D[3];
    u16 unk40;
    u16 unk42;
    u8 filler44[8];
    u8 unk4C;
};

extern struct IntroData2 gUnknown_0201A450;

extern u8 gUnknown_0201C1B8;
extern u8 gUnknown_0202ADD4;
extern s16 gUnknown_0202C594;
extern s32 gUnknown_02019C30;
extern u32 gUnknown_0201C188;
extern s16 gUnknown_0202A578;
extern s32 gUnknown_0202BEF0;
extern s8 gUnknown_0202C5A8;

void sub_96A8(void)
{
    gUnknown_0201A450.unk10 = 0x78;
    gUnknown_0201A450.unk12 = 0x50;
    gUnknown_0201A450.unk18 = 0;
    gUnknown_0201A450.unk1C = 1;
    gUnknown_0201A450.unk30 = 0x9C;
    gUnknown_0201A450.unk32 = 0x92;
    gUnknown_0201A450.unk3C = 0;
    gUnknown_0201A450.unk3A = 0;
    gUnknown_0201A450.unk20 = 0x9D;
    gUnknown_0201A450.unk22 = 0x93;
    gUnknown_0201A450.unk2C = 0;
    gUnknown_0201A450.unk40 = 0x80;
    gUnknown_0201A450.unk42 = 0x80;
    gUnknown_0201A450.unk4C = 1;

    gUnknown_0202ADA0.unk0 = 0xFFA8;
    gUnknown_0202ADA0.unk2 = 0xFFCA;
    gUnknown_0202ADA0.unk8 = 0;
    gUnknown_0202ADA0.unkA = 0;
    gUnknown_0202ADA0.unkC = 0x100;
    gUnknown_0202ADA0.unkE = 0;
    gUnknown_0202ADA0.unk14 = 0;
    gUnknown_0202ADA0.unk24 = 0xFB;
    gUnknown_0202ADA0.unk26 = 0;
    gUnknown_0202ADA0.unk2C = 0;
    gUnknown_0202ADA0.unk18 = 0;
    gUnknown_0202ADA0.unk1A = 0;

    gUnknown_0201A450.unk0 = 0x78;
    gUnknown_0201A450.unk2 = 0x50;
    gUnknown_0201A450.unk8 = 0;
    gUnknown_0201A450.unkA = 0;
    gUnknown_0201A450.unkC = 1;

    gUnknown_0201C1B8 = 0;
    gUnknown_0202ADD4 = 16;
    gUnknown_0202C594 = 0;
    gUnknown_02019C30 = 0x100;
    gUnknown_0201C188 = 0x100;
    gUnknown_0202BF10 = 0;
    gUnknown_0202A578 = 0;
    gUnknown_0202BEF0 = 32;
    gUnknown_0202C5A8 = 8;
}

extern s16 gUnknown_086A77A8[][10][2];

extern void sub_9CB8(void);

void sub_978C(void)
{
    sub_9CB8();
    if (gUnknown_0201A450.unk8 == 0x24)
    {
        gUnknown_0201A450.unkA++;
        if (gUnknown_0201A450.unkA > 0x1B)
        {
            gUnknown_0201A450.unkA = 0;
            gUnknown_0202A578 = 0;
            gUnknown_0202C790++;
        }
    }
    else
    {
        gUnknown_0201A450.unkA++;
        if (gUnknown_0201A450.unkA > 1)
        {
            gUnknown_0201A450.unkA = 0;
            gUnknown_0201A450.unk8++;
        }
        if (gUnknown_0202BF10 >= gUnknown_086A77A8[gUnknown_0202C5A8][gUnknown_0202A578][1])
        {
            m4aSongNumStart(gUnknown_086A77A8[gUnknown_0202C5A8][gUnknown_0202A578][0]);
            gUnknown_0202A578++;
        }
    }
}

extern void sub_9D70(void);

void sub_9830(void)
{
    gUnknown_02019C30 -= 16;
    gUnknown_0201C188 -= 16;
    gUnknown_0201A450.unk0--;
    if (gUnknown_02019C30 < 32)
    {
        gUnknown_0201A450.unkA = 0;
        gUnknown_0201A450.unk8 = 0x25;
        gUnknown_0202C790++;
    }
    sub_9D70();
}

void sub_9878(void)
{
    gUnknown_0201A450.unkA++;
    if (gUnknown_0201A450.unkA > 3)
    {
        gUnknown_0201A450.unkA = 0;
        gUnknown_0201A450.unk0 = 0x78;
        gUnknown_0201A450.unk2 = 0x58;
        gUnknown_0201A450.unkC = 1;
        m4aSongNumStart(0xD8);
        gUnknown_0202C790++;
    }
}

void sub_98B4(void)
{
    if (gUnknown_0201A450.unk8 == 0x2B)
    {
        gUnknown_0201A450.unkA++;
        if (gUnknown_0201A450.unkA > 1)
        {
            gUnknown_0201A450.unkC = 0;
            sub_10170(gIntroScene1Sprites_Pals + 0xE0, (void *)(PLTT + 0xE0), 0x20, 0);
            m4aSongNumStart(8);
            gUnknown_0202C790++;
        }
    }
    else
    {
        gUnknown_0201A450.unkA++;
        if (gUnknown_0201A450.unkA > 1)
        {
            gUnknown_0201A450.unkA = 0;
            gUnknown_0201A450.unk8++;
        }
    }
    sub_9CB8();
}

extern void sub_9E90(void);

void sub_9920(void)
{
    if (gUnknown_0202BF10 % 3 == 0)
    {
        if (gUnknown_0202C594 < 8)
        {
            gUnknown_0202C594++;
            gUnknown_0201C1B8++;
            gUnknown_0202ADD4--;
        }
        else
        {
            sub_10708(gUnknown_0201C1C0, (void *)(VRAM + 0x36E0), 8, 8);
            gUnknown_0202C790++;
        }
        gUnknown_0201A450.unk18 = 1 - gUnknown_0201A450.unk18;
    }
    sub_9E90();
}

extern struct {s16 unk0; s16 unk2;} gUnknown_086A7768[];
extern s16 gUnknown_086A7788[];

void sub_999C(void)
{
    if (gUnknown_0202BEF0 > 0)
    {
        gUnknown_0202BEF0 -= 2;
        if (gUnknown_0202BEF0 <= 0)
            gUnknown_0202BEF0 = 0;
        sub_10170(gIntroScene1Sprites_Pals, (void *)(PLTT), 0x200, gUnknown_0202BEF0);
        sub_10170(gIntroScene1Sprites_Pals, (void *)(PLTT + 0x200), 0x20, gUnknown_0202BEF0);
    }
    if (gUnknown_0202BF10 % 3 == 0)
        gUnknown_0201A450.unk18 = 1 - gUnknown_0201A450.unk18;
    
    gUnknown_0202ADA0.unk0--;
    if (gUnknown_0202BF10 % 2 == 0)
        gUnknown_0202ADA0.unk2--;

    gMain.unk2E8[0].unk0 = gUnknown_0202ADA0.unk0;
    gMain.unk2E8[0].unk2 = gUnknown_0202ADA0.unk2;

    gUnknown_0202ADA0.unkA++;

    if (gUnknown_0202ADA0.unkA > gUnknown_086A7768[gUnknown_0202ADA0.unk8].unk2)
    {
        sub_10708(&gUnknown_0201C1C0[gUnknown_086A7788[gUnknown_0202ADA0.unk8] * 2], (void *)(VRAM + 0x36E0), 8, 8);
        gUnknown_0202ADA0.unk8++;
        if (gUnknown_0202ADA0.unk8 > 3)
        {
            gUnknown_0201A450.unk3C = 1;
            gUnknown_0201A450.unk2C = 1;
            gUnknown_0201A450.unk1C = 0;
            gUnknown_0202ADA0.unk14 = 0;
            gUnknown_0202C790++;
        }
    }
    sub_9E90();
}
