#pragma once

#include <iostream>

namespace bmstu
{
template <typename T>
class basic_string;

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

template <typename T>
class basic_string;

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;
// typedef basic_string<char8_t> u8string;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

template <typename T>
#ifdef _MSC_VER
class basic_string
#else
class basic_string
#endif
{
   public:
	/// Конструктор по умолчанию
	basic_string() : ptr_(new T[1]{0}), size_(0) {}

	basic_string(size_t size) : ptr_(new T[size + 1]), size_(size) {}

	basic_string(std::initializer_list<T> il)
		: ptr_(new T[il.size() + 1]), size_(il.size())
	{
	}

	/// Конструктор с параметром си-с
	basic_string(const T* c_str) {}

	/// Конструктор копирования
	basic_string(const basic_string& other) {}

	/// Перемещающий конструктор
	basic_string(basic_string&& dying) {}

	/// Деструктор
	~basic_string() {}

	/// Геттер на си-строку
	const T* c_str() const { return ptr_; }

	size_t size() const { return size_; }

	/// Оператор копирующего присваивания
	basic_string& operator=(basic_string&& other) { return *this; }

	/// Оператор копирующего присваивания си строки
	basic_string& operator=(const T* c_str) { return *this; }

	/// Оператор копирующего присваивания
	basic_string& operator=(const basic_string& other) { return *this; }

	friend basic_string<T> operator+(const basic_string<T>& left,
									 const basic_string<T>& right)
	{
		basic_string result;
		result.size_ = left.size_ + right.size_;
		result.ptr_ = new T[result.size_ + 1];
		result.copy_data_(left.c_str());
		for (size_t i = 0; i < right.size_; ++i)
		{
			result.ptr_[i + left.size_] = right.ptr_[i];
		}
		result.ptr_[result.size_] = 0;
		return result;
	}

	template <typename S>
	friend S& operator<<(S& os, const simple_basic_string& obj)
	{
		os << obj.c_str();
		return os;
	}

	template <typename S>
	friend S& operator>>(S& is, simple_basic_string& obj)
	{
		is >> noskipws;
		T symbol;
		obj.clean_();
		obj.size_ = 0;
		obj.ptr_ = new T[1]{0};
		while (is >> symbol)
		{
			obj += symbol;
		}
		return is;
	}

	basic_string& operator+=(const basic_string& other) { return *this; }

	basic_string& operator+=(T symbol) { return *this; }

	T& operator[](size_t index) noexcept { return *(ptr_ + index); }

	T& operator[](size_t index) const
	{
		if (index >= size_)
		{
			throw std::out_of_range("Index out of range");
		}
		return ptr_[index];
	}

	basic_string& operator--()
	{
		T* new_ptr = new T[size_];
		for (size_t i = 1; i < size_; ++i)
		{
			new_ptr[i - 1] = ptr_[i];
		}
		delete[] ptr_;
		ptr_ = new_ptr;
		--size_;
		new_ptr[size_] = '\0';
		return *this;
	}

   private:
	size_t size_ = 0;
	T* ptr_ = nullptr;

	static size_t strlen_(const T* str)
	{
		size_t len = 0;
		while (str[len] != 0)
		{
			++len;
		}
		return len;
	}

	void clean_()
	{
		delete[] ptr_;
		ptr_ = nullptr;
		size_ = 0;
	}

	void copy_data_(const T* c_str)
	{
		for (size_t i = 0; i < size_; ++i)
		{
			ptr_[i] = c_str[i];
		}
		ptr_[size_] = 0;
	}
};

}  // namespace bmstu
