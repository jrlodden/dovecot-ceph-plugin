/*
 * rados-storage.h
 *
 *  Created on: Sep 4, 2017
 *      Author: jan
 */

#ifndef SRC_LIBRMB_INTERFACES_RADOS_STORAGE_INTERFACE_H_
#define SRC_LIBRMB_INTERFACES_RADOS_STORAGE_INTERFACE_H_

#include "../rados-mail-object.h"
#include "rados-cluster-interface.h"
#include <rados/librados.hpp>

namespace librmb {

class RadosStorage {
 public:
  virtual ~RadosStorage(){};

  virtual librados::IoCtx &get_io_ctx() = 0;
  virtual int stat_object(const std::string &oid, uint64_t *psize, time_t *pmtime) = 0;
  virtual void set_namespace(const std::string &nspace) = 0;
  virtual int get_max_write_size() = 0;
  virtual int get_max_write_size_bytes() = 0;

  virtual int split_buffer_and_exec_op(const char *buffer, size_t buffer_length, RadosMailObject *current_object,
                                       librados::ObjectWriteOperation *write_op_xattr, uint64_t max_write) = 0;

  virtual int read_mail(const std::string &oid, uint64_t *size_r, char *mail_buffer) = 0;
  virtual int load_xattr(RadosMailObject *mail) = 0;
  virtual int set_xattr(const std::string &oid, RadosXAttr &xattr) = 0;

  virtual int delete_mail(RadosMailObject *mail) = 0;
  virtual int delete_mail(std::string oid) = 0;

  virtual int aio_operate(librados::IoCtx *io_ctx_, const std::string &oid, librados::AioCompletion *c,
                          librados::ObjectWriteOperation *op) = 0;
  virtual librados::NObjectIterator find_objects(RadosXAttr *attr) = 0;
  virtual int open_connection(const std::string &poolname, const std::string &ns) = 0;
};

}  // namespace librmb

#endif /* SRC_LIBRMB_INTERFACES_RADOS_STORAGE_INTERFACE_H_ */