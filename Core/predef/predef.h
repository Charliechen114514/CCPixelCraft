#ifndef PREDEF_H
#define PREDEF_H

/* Followings are using to mark the memory management type */

#define USE_OBJTREE
#define BORROW_FROM_EXTERN
#define DISABLE_COPY(CLASS)                  \
    CLASS(const CLASS&)            = delete; \
    CLASS& operator=(const CLASS&) = delete;

#endif  // PREDEF_H
