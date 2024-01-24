#pragma once

#ifdef D_MSVC
#if (_ITERATOR_DEBUG_LEVEL > 0)
#define D_DEBUG
#else //! (_ITERATOR_DEBUG_LEVEL > 0)
#define D_RELEASE
#endif // (_ITERATOR_DEBUG_LEVEL > 0)
#endif // D_MSVC