<h1 align=center>Jansson</h1> 
<div align=center>

[![CI](https://github.com/rejchev/sm-jansson/actions/workflows/ci.yml/badge.svg)](https://github.com/rejchev/sm-jansson/)
[![Downloads](https://img.shields.io/github/downloads/rejchev/sm-jansson/total?color=%2332c955)]()
[![LICENSE](https://img.shields.io/github/license/rejchev/sm-jansson)](LICENSE)

</div>

## About
This is an extension that implements Json API for SourceMod based on [Jansson](https://github.com/akheron/jansson) 

### Required dependencies

- [SourceMod](https://www.sourcemod.net/downloads.php?branch=stable)

### Supported OS
- Windows
- Linux

### Supported SDK
- Any

## Getting Started

### Installation

1. Go on [releases](https://github.com/rejchev/sm-jansson/releases)
2. Download release for your OS
3. Unpack on your dedicated game server
4. Congratulation 🥳


## Usage

### SourcePawn API
 
```c
// if u need to use simple json builder
#define JSON_INCLUDE_BUILDER

// lib
#include <jansson>

// some func
public void OnMapStart() {
    
    // empty JsonObject
    Json jsonObject = new Json("{}");
    
    // empty JsonArray
    Json jsonArray = new Json("[]");
    
    // { 
    //      "array": [
    //          
    //      ] 
    // }
    asJSONO(jsonObject).Set("array", jsonArray);
    
    delete jsonArray;
    
    // simple builder
    jsonObject = asJSONB(jsonObject)
        .SetInt("int", 12)
        .SetString("string", "rejchev")
        .SetFloat("float", 111.111)
        .SetInt64("int64", "9999999999999")
        .Build();
    
    // ...
    
    char buffer[1024];
    if(!jsonObject.Dump(buffer, sizeof(buffer), JsonPretty(4)|JsonRealPrecision(3), true))
        delete jsonObject;
    
    LogMessage(buffer);
    
    // output:
    //
    // { 
    //      "array": [
    //          
    //      ],
    //      "int":  12,
    //      "string":   "rejchev",
    //      "float":    111.111,
    //      "int64":    9999999999999
    // }
}
```
Another example: [test.sp](https://github.com/rejchev/sm-jansson/blob/main/pawn/scripting/test.sp) </br>
More information: [jansson.inc](https://github.com/rejchev/sm-jansson/blob/main/pawn/scripting/include/jansson.inc)

### SourceMod Extension API
```c++

#include <IJansson.h>

nJansson::IJansson* g_pJansson = nullptr;

void Sample::SDK_OnAllLoaded()
{
	SM_GET_LATE_IFACE(JANSSON, g_pJansson);
}
```
Header: [IJansson.h](https://github.com/rejchev/sm-jansson/blob/main/public/IJansson.h) </br>
More information: [SourceMod WiKi](https://wiki.alliedmods.net/Writing_Extensions)


## Contacts
- [Telegram](https://t.me/rejsoft)

## Donuts
- BTC: ```1MFXSopgnJaZrcJ1t8Ydw9rHvKT13GLGsf```
- USDT(TON): ```UQAuSiZ3Vbk6PNat69D_Nik-br63EI0kOmGsOXG3YDchmsJl```
