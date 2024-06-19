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

#define TK_NODEFAULT TK_ERROR("Hit end of switch in ", __FUNCTION__)

#define TK_STL_HASH(type, impl)    \
    namespace std                  \
    {                              \
    template <>                    \
    struct hash<type>              \
    {                              \
        TkSizeType operator() impl \
    };                             \
    }

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &);            \
    void operator=(const TypeName &)

#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
    TypeName();                                  \
    DISALLOW_COPY_AND_ASSIGN(TypeName)