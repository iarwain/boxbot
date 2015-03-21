/*
 * Player.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: loki
 */

#include "Player.h"
#include "Game.h"

static  const orxFLOAT sfAcceleration = orx2F(4.f);
static  const orxFLOAT sfMaxSpeed     = orx2F(150.f);
static  const orxFLOAT sfGravity      = orx2F(981.f);
static  const orxFLOAT sfMaxFall      = orx2F(500.f);
static  const orxFLOAT sfJump         = orx2F(550.f);

static  const orxS32   ss32HorizontalRays = 6;
static  const orxS32   ss32VerticalRays   = 4;
static  const orxU32   sfMargin           = orx2F(2.f);

static  const orxSTRING szPlatform   = "Platform";

void Player::OnCreate()
{
  orxVector_Copy(&mvVelocity, &orxVECTOR_0);
  mbGrounded = orxFALSE;
  mbFalling = orxFALSE;
  mu32CollisionFlag = orxPhysics_GetCollisionFlagValue(szPlatform);
  mfHorizontalAxis = orxFLOAT_0;
  mbJump = orxFALSE;

  Game::GetInstance().RegisterPlayer(*this);
}

void Player::OnDelete()
{
  Game::GetInstance().UnregisterPlayer();
}

void Player::Update(const orxCLOCK_INFO &_rstInfo)
{
  orxVECTOR vPosition, vDelta;

  // Apply Gravity
  ApplyGravity(_rstInfo.fDT);

  // Apply horizontal input
  orxFLOAT fNewVelocityX = mvVelocity.fX;
  if(mfHorizontalAxis != orxFLOAT_0)
  {
    fNewVelocityX += sfAcceleration * mfHorizontalAxis;
    fNewVelocityX = orxCLAMP(fNewVelocityX, -sfMaxSpeed, sfMaxSpeed);
  }
  else if (mvVelocity.fX != orxFLOAT_0 && mbGrounded)
  {
    fNewVelocityX += sfAcceleration / 2 * (mvVelocity.fX > 0 ? -orxFLOAT_1 : orxFLOAT_1);
  }
  mvVelocity.fX = fNewVelocityX;

  if(mbJump && mbGrounded)
  {
    mvVelocity.fY = -sfJump;
    mbGrounded = orxFALSE;
  }
  mbJump = orxFALSE;

  // Update position
  GetPosition(vPosition, orxTRUE);
  orxVector_Mulf(&vDelta, &mvVelocity, _rstInfo.fDT);
  orxVector_Add(&vPosition, &vPosition, &vDelta);
  SetPosition(vPosition, orxTRUE);
}

void Player::Left()
{
  mfHorizontalAxis = -orxFLOAT_1;
}

void Player::Right()
{
  mfHorizontalAxis = orxFLOAT_1;
}

void Player::Stop()
{
  mfHorizontalAxis = orxFLOAT_0;
}

void Player::Jump()
{
  mbJump = orxTRUE;
}

void Player::ApplyGravity(orxFLOAT _fDT)
{
  if(!mbGrounded)
  {
    orxVector_Set(&mvVelocity, mvVelocity.fX, orxMIN(mvVelocity.fY + sfGravity * _fDT, sfMaxFall), orxFLOAT_0);
  }

  if(mvVelocity.fY > orxFLOAT_0)
  {
    mbFalling = orxTRUE;
  }

  if(mbGrounded || mbFalling)
  {
    orxVECTOR vStartPoint, vEndPoint;
    orxFLOAT fDistance;
    orxBOOL bConnected = orxFALSE;

    orxOBOX stBox;
    orxVECTOR vCenter, vSize, vScale;

    orxObject_GetBoundingBox(GetOrxObject(), &stBox);
    orxOBox_GetCenter(&stBox, &vCenter);
    orxObject_GetSize(GetOrxObject(), &vSize);
    GetScale(vScale, orxTRUE);
    orxVector_Mul(&vSize, &vSize, &vScale);

    fDistance = sfMargin + (mbGrounded ? sfMargin : orxMath_Abs(mvVelocity.fY * _fDT));
    orxVector_Set(&vStartPoint, vCenter.fX - vSize.fX / 2 + sfMargin, vCenter.fY + vSize.fY / 2 - sfMargin, orxFLOAT_0);
    orxVector_Set(&vEndPoint, vCenter.fX + vSize.fX / 2 - sfMargin, vCenter.fY + vSize.fY / 2 - sfMargin, orxFLOAT_0);

    for(int i = 0; i < ss32VerticalRays; i ++)
    {
      orxVECTOR vOrigin, vEnd, vContact;

      orxFLOAT fLerpAmount = orx2F(i) / orx2F(ss32VerticalRays - 1);
      orxVector_Lerp(&vOrigin, &vStartPoint, &vEndPoint, fLerpAmount);
      orxVector_Copy(&vEnd, &vOrigin);
      vEnd.fY += fDistance;

      orxBODY* pBody = orxBody_Raycast(&vOrigin, &vEnd,	0xFFFF,	mu32CollisionFlag, orxTRUE,	&vContact, orxNULL);

      bConnected = pBody != orxNULL;

      if(bConnected)
      {
        orxVECTOR vPosition;
        mbGrounded = orxTRUE;
        mbFalling = orxFALSE;
        GetPosition(vPosition, orxTRUE);
        vPosition.fY = vContact.fY;
        SetPosition(vPosition, orxTRUE);
        orxVector_Set(&mvVelocity, mvVelocity.fX, orxFLOAT_0, orxFLOAT_0);
        break;
      }
    }

    if(!bConnected)
    {
      mbGrounded = orxFALSE;
    }
  }
}
