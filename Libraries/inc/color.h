/*
 * color.h
 *
 *  Created on: 2016��3��18��
 *      Author: Westlor
 */

#ifndef LIBRARIES_INC_COLOR_H_
#define LIBRARIES_INC_COLOR_H_

#define	RGB(a, b, c)			((a<<16)+(b<<8)+(c<<0))

#define LIGHTPINK				RGB(255, 182, 193)		// ǳ�ۺ�
#define PINK					RGB(255, 192, 203)		// �ۺ�
#define CRIMSON					RGB(220,  20,  60)		// �ɺ� (���)
#define LAVENDERBLUSH			RGB(255, 240, 245)		// ���Ϻ�
#define PALEVIOLETRED			RGB(219, 112, 147)		// ����������
#define HOTPINK					RGB(255, 105, 180)		// ����ķۺ�
#define DEEPPINK				RGB(255,  20, 147)		// ��ۺ�
#define MEDIUMVIOLETRED			RGB(199,  21, 133)		// ����������
#define ORCHID					RGB(218, 112, 214)		// ������
#define THISTLE					RGB(216, 191, 216)		// ��
#define PLUM					RGB(221, 160, 221)		// ������
#define VIOLET					RGB(238, 130, 238)		// ������
#define MAGENTA					RGB(255,   0, 255)		// ��� (Ʒ�� õ���)
#define FUCHSIA					RGB(255,   0, 255)		// ��������(�Ϻ�ɫ)
#define DARKMAGENTA				RGB(139,   0, 139)		// �����
#define PURPLE					RGB(128,   0, 128)		// ��ɫ
#define MEDIUMORCHID			RGB(186,  85, 211)		// ��������
#define DARKVIOLET				RGB(148,   0, 211)		// ��������
#define DARKORCHID				RGB(153,  50, 204)		// ��������
#define INDIGO					RGB( 75,   0, 130)		// ���� (����ɫ)
#define BLUEVIOLET				RGB(138,  43, 226)		// ��������
#define MEDIUMPURPLE			RGB(147, 112, 219)		// ����ɫ
#define MEDIUMSLATEBLUE			RGB(123, 104, 238)		// �а�����
#define SLATEBLUE				RGB(106,  90, 205)		// ������
#define DARKSLATEBLUE			RGB( 72,  61, 139)		// ��������
#define LAVENDER				RGB(230, 230, 250)		// Ѭ�²ݵ���
#define GHOSTWHITE				RGB(248, 248, 255)		// �����
#define BLUE					RGB(  0,   0, 255)		// ����
#define MEDIUMBLUE				RGB(  0,   0, 205)		// ����ɫ
#define MIDNIGHTBLUE			RGB( 25,  25, 112)		// ��ҹ��
#define DARKBLUE				RGB(  0,   0, 139)		// ����ɫ
#define NAVY					RGB(  0,   0, 128)		// ������
#define ROYALBLUE				RGB( 65, 105, 225)		// �ʼ��� (����)
#define CORNFLOWERBLUE			RGB(100, 149, 237)		// ʸ������
#define LIGHTSTEELBLUE			RGB(176, 196, 222)		// ������
#define LIGHTSLATEGRAY			RGB(119, 136, 153)		// ��ʯ���
#define SLATEGRAY				RGB(112, 128, 144)		// ʯ���
#define DODGERBLUE				RGB( 30, 144, 255)		// ������
#define ALICEBLUE				RGB(240, 248, 255)		// ����˿��
#define STEELBLUE				RGB( 70, 130, 180)		// ���� (����)
#define LIGHTSKYBLUE			RGB(135, 206, 250)		// ������ɫ
#define SKYBLUE					RGB(135, 206, 235)		// ����ɫ
#define DEEPSKYBLUE				RGB(  0, 191, 255)		// ������
#define LIGHTBLUE				RGB(173, 216, 230)		// ����
#define POWDERBLUE				RGB(176, 224, 230)		// ��ҩ��
#define CADETBLUE				RGB( 95, 158, 160)		// ������
#define AZURE					RGB(240, 255, 255)		// ε��ɫ
#define LIGHTCYAN				RGB(224, 255, 255)		// ����ɫ
#define PALETURQUOISE			RGB(175, 238, 238)		// ���̱�ʯ
#define CYAN					RGB(  0, 255, 255)		// ��ɫ
#define AQUA					RGB(  0, 255, 255)		// ˮɫ
#define DARKTURQUOISE			RGB(  0, 206, 209)		// ���̱�ʯ
#define DARKSLATEGRAY			RGB( 47,  79,  79)		// ��ʯ���
#define DARKCYAN				RGB(  0, 139, 139)		// ����ɫ
#define TEAL					RGB(  0, 128, 128)		// ˮѼɫ
#define MEDIUMTURQUOISE			RGB( 72, 209, 204)		// ���̱�ʯ
#define LIGHTSEAGREEN			RGB( 32, 178, 170)		// ǳ������
#define TURQUOISE				RGB( 64, 224, 208)		// �̱�ʯ
#define AQUAMARINE				RGB(127, 255, 212)		// ��ʯ����
#define MEDIUMAQUAMARINE		RGB(102, 205, 170)		// �б�ʯ����
#define MEDIUMSPRINGGREEN		RGB(  0, 250, 154)		// �д���ɫ
#define MINTCREAM				RGB(245, 255, 250)		// ��������
#define SPRINGGREEN				RGB(  0, 255, 127)		// ����ɫ
#define MEDIUMSEAGREEN			RGB( 60, 179, 113)		// �к�����
#define SEAGREEN				RGB( 46, 139,  87)		// ������
#define HONEYDEW				RGB(240, 255, 240)		// �۹�ɫ
#define LIGHTGREEN				RGB(144, 238, 144)		// ����ɫ
#define PALEGREEN				RGB(152, 251, 152)		// ����ɫ
#define DARKSEAGREEN			RGB(143, 188, 143)		// ��������
#define LIMEGREEN				RGB( 50, 205,  50)		// ��������
#define LIME					RGB(  0, 255,   0)		// ������
#define FORESTGREEN				RGB( 34, 139,  34)		// ɭ����
#define GREEN					RGB(  0, 128,   0)		// ����
#define DARKGREEN				RGB(  0, 100,   0)		// ����ɫ
#define CHARTREUSE				RGB(127, 255,   0)		// ���ؾ��� (����ɫ)
#define LAWNGREEN				RGB(124, 252,   0)		// ��ƺ��
#define GREENYELLOW				RGB(173, 255,  47)		// �̻�ɫ
#define DARKOLIVEGREEN			RGB( 85, 107,  47)		// �������
#define YELLOWGREEN				RGB(154, 205,  50)		// ����ɫ
#define OLIVEDRAB				RGB(107, 142,  35)		// ��魺�ɫ
#define BEIGE					RGB(245, 245, 220)		// ��ɫ(����ɫ)
#define LIGHTGOLDENRODYELLOW	RGB(250, 250, 210)		// ���ջ�
#define IVORY					RGB(255, 255, 240)		// ����
#define LIGHTYELLOW				RGB(255, 255, 224)		// ǳ��ɫ
#define YELLOW					RGB(255, 255,   0)		// ����
#define OLIVE					RGB(128, 128,   0)		// ���
#define DARKKHAKI				RGB(189, 183, 107)		// �ߴ��
#define LEMONCHIFFON			RGB(255, 250, 205)		// ���ʳ�
#define PALEGOLDENROD			RGB(238, 232, 170)		// �Ҿջ�
#define KHAKI					RGB(240, 230, 140)		// ��ߴ��
#define GOLD					RGB(255, 215,   0)		// ��ɫ
#define CORNSILK				RGB(255, 248, 220)		// ����˿ɫ
#define GOLDENROD				RGB(218, 165,  32)		// ��ջ�
#define DARKGOLDENROD			RGB(184, 134,  11)		// ����ջ�
#define FLORALWHITE				RGB(255, 250, 240)		// ���İ�ɫ
#define OLDLACE					RGB(253, 245, 230)		// ����˿
#define WHEAT					RGB(245, 222, 179)		// С��ɫ
#define MOCCASIN				RGB(255, 228, 181)		// ¹Ƥѥ
#define ORANGE					RGB(255, 165,   0)		// ��ɫ
#define PAPAYAWHIP				RGB(255, 239, 213)		// ��ľ��
#define BLANCHEDALMOND			RGB(255, 235, 205)		// ���׵�����ɫ
#define NAVAJOWHITE				RGB(255, 222, 173)		// ������
#define ANTIQUEWHITE			RGB(250, 235, 215)		// �Ŷ���
#define TAN						RGB(210, 180, 140)		// ��ɫ
#define BURLYWOOD				RGB(222, 184, 135)		// Ӳľɫ
#define BISQUE					RGB(255, 228, 196)		// ������
#define DARKORANGE				RGB(255, 140,   0)		// ���ɫ
#define LINEN					RGB(250, 240, 230)		// ���鲼
#define PERU					RGB(205, 133,  63)		// ��³
#define PEACHPUFF				RGB(255, 218, 185)		// ����ɫ
#define SANDYBROWN				RGB(244, 164,  96)		// ɳ��ɫ
#define CHOCOLATE				RGB(210, 105,  30)		// �ɿ���
#define SADDLEBROWN				RGB(139,  69,  19)		// ����ɫ
#define SEASHELL				RGB(255, 245, 238)		// ������
#define SIENNA					RGB(160,  82,  45)		// ������ɫ
#define LIGHTSALMON				RGB(255, 160, 122)		// ǳ������ɫ
#define CORAL					RGB(255, 127,  80)		// ɺ��
#define ORANGERED				RGB(255,  69,   0)		// �Ⱥ�ɫ
#define DARKSALMON				RGB(233, 150, 122)		// ������(����)ɫ
#define TOMATO					RGB(255,  99,  71)		// ���Ѻ�
#define MISTYROSE				RGB(255, 228, 225)		// ����õ��
#define SALMON					RGB(250, 128, 114)		// ����(����)ɫ
#define SNOW					RGB(255, 250, 250)		// ѩ
#define LIGHTCORAL				RGB(240, 128, 128)		// ��ɺ��ɫ
#define ROSYBROWN				RGB(188, 143, 143)		// õ����ɫ
#define INDIANRED				RGB(205,  92,  92)		// ӡ�Ⱥ�
#define RED						RGB(255,   0,   0)		// ����
#define BROWN					RGB(165,  42,  42)		// ��ɫ
#define FIREBRICK				RGB(178,  34,  34)		// �ͻ�ש
#define DARKRED					RGB(139,   0,   0)		// ���ɫ
#define MAROON					RGB(128,   0,   0)		// ��ɫ
#define WHITE					RGB(255, 255, 255)		// ����
#define WHITESMOKE				RGB(245, 245, 245)		// ����
#define GAINSBORO				RGB(220, 220, 220)		// ��˹���޻�ɫ
#define LIGHTGREY				RGB(211, 211, 211)		// ǳ��ɫ
#define SILVER					RGB(192, 192, 192)		// ����ɫ
#define DARKGRAY				RGB(169, 169, 169)		// ���ɫ
#define GRAY					RGB(186, 183, 186)		// ��ɫ(*)
#define DIMGRAY					RGB(105, 105, 105)		// �����Ļ�ɫ
#define BLACK					RGB(  0,   0,   0)		// ����


#endif /* LIBRARIES_INC_COLOR_H_ */
