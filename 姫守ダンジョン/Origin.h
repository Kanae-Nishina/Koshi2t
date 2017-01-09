//
//	@file	Origin.h
//	@brief	�e�t�@�C���ŕK�v�ȃC���N���[�h�t�@�C���ƃ}�N����`
//	@date	2016/11/08
//	@author	�m�ȍ��c
//	@note	�T���v���R�[�h�����MAIN�N���X����ڍs���܂����B

#pragma once
#include <stdio.h>
#include <windows.h>
#include <d3dx9.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
#include "./DebugDraw/D3D11_TEXT.h"
#include "./UI/D3D11_SPRITE.h"
#include "./Compiled/include/Effekseer.h"
#include "./Compiled/include/EffekseerRendererDX11.h"

//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

#if _DEBUG
#pragma comment(lib, "./Compiled/lib/VS2015/Debug/Effekseer.lib" )
#pragma comment(lib, "./Compiled/lib/VS2015/Debug/EffekseerRendererDX11.lib" )
//#pragma comment(lib, "VS2015/Debug/EffekseerSoundXAudio2.lib" )
#else
#pragma comment(lib, "./Compiled/lib/VS2015/Release/Effekseer.lib" )
#pragma comment(lib, "./Compiled/lib/VS2015/Release/EffekseerRendererDX11.lib" )
//#pragma comment(lib, "VS2015/Release/EffekseerSoundXAudio2.lib" )
#endif

//�萔��`
#define WINDOW_WIDTH 1920	//�E�B���h�E��
#define WINDOW_HEIGHT 1080 //�E�B���h�E����
#define APP_NAME L"�P��_���W����"	//�Q�[���^�C�g��
const int FPS = 60;				//FPS



//�}�N��
#define SAFE_RELEASE(x) if(x){x->Release(); x=0;}
#define SAFE_DELETE(x) if(x){delete x; x=0;}
#define SAFE_DELETE_ARRAY(p){ if(p){ delete[] (p);   (p)=NULL;}}
//�摜��
#define PIC2D_NUM 25