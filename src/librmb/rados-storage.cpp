/* Copyright (c) 2017 Tallence AG and the authors, see the included COPYING file */

#include <string>

#include <rados/librados.hpp>

#include "rados-storage.h"

using namespace librados;  // NOLINT
using namespace librmb;    // NOLINT

using std::string;

#define DICT_USERNAME_SEPARATOR '/'

RadosStorage::RadosStorage(librados::IoCtx *ctx, const string &username) : io_ctx(*ctx), username(username) {}

RadosStorage::~RadosStorage() { get_io_ctx().close(); }
