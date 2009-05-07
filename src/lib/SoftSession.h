/* $Id$ */

/*
 * Copyright (c) 2008-2009 .SE (The Internet Infrastructure Foundation).
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/************************************************************
*
* This class defines a session
* It holds the current state of the session
*
************************************************************/

#ifndef SOFTHSM_SOFTSESSION_H
#define SOFTHSM_SOFTSESSION_H 1

#include "pkcs11_unix.h"
#include "SoftFind.h"
#include "SoftDatabase.h"
#include "SoftKeyStore.h"
#include "SoftSlot.h"

// Includes for the crypto library
#include <botan/pipe.h>
#include <botan/pubkey.h>
#include <botan/pk_keys.h>
#include <botan/auto_rng.h>
using namespace Botan;

class SoftFind;
class SoftDatabase;
class SoftKeyStore;
class SoftSlot;

class SoftSession {
  public:
    SoftSession(CK_FLAGS rwSession, SoftSlot *givenSlot);
    ~SoftSession();

    SoftSlot *currentSlot;
    bool isReadWrite();
    CK_VOID_PTR pApplication;
    CK_NOTIFY Notify;
    CK_STATE getSessionState();

    // Find
    SoftFind *findAnchor;
    SoftFind *findCurrent;
    bool findInitialized;

    // Digest
    Pipe *digestPipe;
    CK_ULONG digestSize;
    bool digestInitialized;

    // Sign
    PK_Signer *pkSigner;
    bool signSinglePart;
    CK_ULONG signSize;
    bool signInitialized;

    // Verify
    PK_Verifier *pkVerifier;
    bool verifySinglePart;
    CK_ULONG verifySize;
    bool verifyInitialized;

    // Key store
    Public_Key* getKey(CK_OBJECT_HANDLE hKey);
    SoftKeyStore *keyStore;

    AutoSeeded_RNG *rng;

    SoftDatabase *db;

  private:
    bool readWrite;
};

#endif /* SOFTHSM_SOFTSESSION_H */