//
//	@file	Origin.h
//	@brief	�e�t�@�C���ŕK�v�ȃC���N���[�h�t�@�C���ƃ}�N����`
//	@date	2016/11/08
//	@outher	�m�ȍ��c
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
#include "./Effect/D3D11_SPRITE.h"

//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//�萔��`
#define WINDOW_WIDTH 1920	//�E�B���h�E��
#define WINDOW_HEIGHT 1080 //�E�B���h�E����
#define APP_NAME L"�P��_���W����"	//�Q�[���^�C�g��
const int FPS = 60;				//FPS


//�}�N��
#define SAFE_RELEASE(x) if(x){x->Release(); x=0;}
#define SAFE_DELETE(x) if(x){delete x; x=0;}
#define SAFE_DELETE_ARRAY(p){ if(p){ delete[] (p);   (p)=NULL;}}
