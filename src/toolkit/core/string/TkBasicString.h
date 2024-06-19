#pragma once

#include <stringzilla/stringzilla.hpp>
#include <toolkit/core/TkTypes.h>
#include <toolkit/memory/allocators/TkSTLAllocator.h>

template <typename Charset_, typename Allocator = TkSTLAllocator<Charset_>>
class cTkBasicString : public ashvardanian::stringzilla::basic_string<Charset_, Allocator>
{
  public:
    using Charset       = Charset_;
    using cTkStringView = ashvardanian::stringzilla::basic_string_slice<typename std::add_const<Charset>::type>;
    using BaseType      = ashvardanian::stringzilla::basic_string<Charset_, Allocator>;
    using ConstPointer  = Charset const *;
    static constexpr TkSizeType NPos = BaseType::npos;

#pragma region Re-Exports
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::basic_string;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::operator=;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::operator[];
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::operator+=;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::operator==;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::operator<=>;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::operator|;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::operator string_span;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::operator string_view;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::operator std::string;

    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::begin;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::end;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::cbegin;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::cend;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::rbegin;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::rend;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::crbegin;
    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::crend;

    using ashvardanian::stringzilla::basic_string<Charset_, Allocator>::c_str;
#pragma endregion

    constexpr cTkBasicString() = default;

    cTkBasicString(const BaseType &base) : BaseType(base) {}
    cTkBasicString(BaseType &&base) noexcept : BaseType(std::move(base)) {}

    cTkBasicString &Append(cTkStringView str) noexcept(false)
    {
        if (!this->try_append(str)) throw std::bad_alloc();
        return *this;
    }

    cTkBasicString &Append(cTkStringView str, TkSizeType pos, TkSizeType length = NPos) noexcept(false)
    {
        return this->Append(str.substr(pos, length));
    }

    cTkBasicString &Append(ConstPointer str, TkSizeType length) noexcept(false) { return this->Append({str, length}); }

    cTkBasicString &Append(ConstPointer str) noexcept(false) { return this->Append(cTkStringView(str)); }

    cTkBasicString &Append(TkSizeType repeats, Charset ch) noexcept(false)
    {
        this->resize(this->size() + repeats, ch);
        return *this;
    }

    cTkBasicString &Append(TkInitialiserList<Charset> other) noexcept(false)
    {
        return this->Append(other.begin(), other.end());
    }

    template <typename InputIterator>
    cTkBasicString &Append(InputIterator first, InputIterator last) noexcept(false)
    {
        this->insert<InputIterator>(cend(), first, last);
        return *this;
    }

    bool Empty() const { return static_cast<const BaseType &>(*this).empty(); }

    cTkBasicString Find(const cTkBasicString &lString) const
    {
        return static_cast<const BaseType &>(*this).find(lString);
    }
    TkSizeType FindLastOf(const cTkBasicString &lString) const
    {
        return static_cast<BaseType>(*this).find_last_of(lString);
    }

    cTkBasicString SubStr(TkSizeType lStart, TkSizeType lCount = NPos) const
    {
        return static_cast<BaseType>(*this).substr(lStart, lCount).c_str();
    }

    template <typename T>
    static cTkBasicString ToString(T lValue)
    {
        return std::to_string(lValue);
    }

    template <typename... Args>
    static cTkBasicString Format(const cTkBasicString lFormat, Args... lArgs)
    {
        std::string_view lTempString = std::string_view(lFormat.c_str());
        std::format_args lFmtArgs    = std::make_format_args(lArgs...);
        std::string lFmtResult       = std::vformat(lTempString, lFmtArgs);
        return cTkBasicString(lFmtResult.c_str());
    }

    TkSizeType Hash() const noexcept { return this->hash(); }
    cTkStringView View() const noexcept { return this->view(); }
};