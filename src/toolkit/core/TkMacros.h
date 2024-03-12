#pragma once

#ifdef D_MSVC
#if (_ITERATOR_DEBUG_LEVEL > 0)
#define D_DEBUG
#else //! (_ITERATOR_DEBUG_LEVEL > 0)
#define D_RELEASE
#endif // (_ITERATOR_DEBUG_LEVEL > 0)

#else //! D_MSVC
#ifdef NDEBUG
#define D_RELEASE
#else //! NDEBUG
#define D_DEBUG
#endif // NDEBUG

#endif // D_MSVC

#define TK_NULL 0

#define TK_STRINGIFY(x) #x