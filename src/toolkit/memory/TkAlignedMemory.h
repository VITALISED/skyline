#pragma once

template <size_t Size, size_t Alignment>
class AlignedMemory
{
  public:
    alignof(Alignment) uint8 data_[Size];
    void *void_data() { return reinterpret_cast<void *>(data_); }
    const void *void_data() const { return reinterpret_cast<const void *>(data_); }
    template <typename Type>
    Type *data_as()
    {
        return reinterpret_cast<Type *>(void_data());
    }
    template <typename Type>
    const Type *data_as() const
    {
        return reinterpret_cast<const Type *>(void_data());
    }

  private:
    void *operator new(size_t);
    void operator delete(void *);
};