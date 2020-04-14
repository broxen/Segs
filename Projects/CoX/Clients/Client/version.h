/*
 * SEGS Client - Super Entity Game Server Client
 * http://www.segs.dev/
 * Copyright (c) 2006 - 2020 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#pragma once

#ifndef SEGS_CLIENT_VERSION
#define SEGS_CLIENT_VERSION "0.0.1" // set in cmake, but defined here if not available
#endif
#ifndef SEGS_CLIENT_BRANCH
#define SEGS_CLIENT_BRANCH "unknown"
#endif
#ifndef SEGS_CLIENT_DESCRIPTION
#define SEGS_CLIENT_DESCRIPTION "unknown"
#endif

#define ProjectOrg "SEGS"
#define ProjectName ProjectOrg " Client"
#define CodeName "Awakening"
#define VersionString ProjectName " v" SEGS_CLIENT_VERSION "-" SEGS_CLIENT_BRANCH " (" CodeName ") [" SEGS_CLIENT_DESCRIPTION "]"
#define ProjectDomain "segs.dev"
#define CopyrightString "Super Entity Game Server\nhttp://github.com/Segs/\nCopyright (c) 2006-2020 Super Entity Game Server Team (see AUTHORS.md)\nThis software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.\n";

// Contains version information for the various server modules
class ClientVersionInfo
{
public:
    static const char *getVersionString(void) { return VersionString; }
    static const char *getVersionNumber(void) { return SEGS_CLIENT_VERSION; }
    static const char *getProjectOrg(void){ return ProjectOrg; }
    static const char *getProjectName(void){ return ProjectName; }
    static const char *getProjectDomain(void){ return ProjectDomain; }
    static const char *getCodeName(void) { return CodeName; }
    static const char *getCopyright(void){ return CopyrightString; }
};

#undef ProjectOrg
#undef ProjectName
#undef CodeName
#undef VersionString
#undef ProjectDomain
#undef CopyrightString
#undef SEGS_CLIENT_VERSION
#undef SEGS_CLIENT_BRANCH
#undef SEGS_CLIENT_DESCRIPTION
