#pragma once
#include <cstddef>
#include <cstdint>
#include <exception>
#include <type_traits>
#include <utility>

namespace bmstu
{
struct nullopt_t
{
	constexpr explicit nullopt_t(int) {}
};
inline constexpr nullopt_t nullopt{0};

class bad_optional_access : public std::exception
{
   public:
	using exception::exception;

	const char* what() const noexcept override { return "Bad optional access"; }
};

template <typename T>
class optional
{
   public:
	optional() = default;

	optional(const T& value) : is_initialized_(true) { new (data_) T(value); }

	optional(T&& value) : is_initialized_(true)
	{
		new (data_) T(std::move(value));
	}

	optional(const optional& other) : is_initialized_(other.is_initialized_)
	{
		if (is_initialized_)
		{
			new (data_) T(*other);
		}
	}

	optional(optional&& other) noexcept : is_initialized_(other.is_initialized_)
	{
		if (is_initialized_)
		{
			new (data_) T(std::move(*other));
			other.is_initialized_ = false;
		}
	}

<<<<<<< HEAD
	optional& operator=(const T& value)
	{
		if (is_initialized_)
		{
			**this = value;
		}
		else
		{
			new (data_) T(value);
			is_initialized_ = true;
		}
		return *this;
	}

	optional& operator=(T&& value)
	{
		if (is_initialized_)
		{
			**this = std::move(value);
		}
		else
		{
			new (data_) T(std::move(value));
			is_initialized_ = true;
		}
		return *this;
	}

	optional& operator=(const optional& value)
	{
		if (this != &value)
		{
			if (value.is_initialized_)
			{
				if (is_initialized_)
				{
					**this = *value;
				}
				else
				{
					new (data_) T(*value);
					is_initialized_ = true;
				}
			}
			else
			{
				reset();
			}
		}
		return *this;
	}

	optional& operator=(optional&& value)
	{
		if (this != &value)
		{
			if (value.is_initialized_)
			{
				if (is_initialized_)
				{
					**this = std::move(*value);
				}
				else
				{
					new (data_) T(std::move(*value));
					is_initialized_ = true;
				}
				value.is_initialized_ = false;
			}
			else
			{
				reset();
			}
		}
		return *this;
	}
=======
	optional& operator=(const T& value) { return *this; }

	optional& operator=(T&& value) { return *this; }

	optional& operator=(const optional& value) { return *this; }

	optional& operator=(optional&& value) { return *this; }
>>>>>>> 66053914fa4dd7d913b4bdd6ecfd9e1959dc4c09

	T& operator*() &
	{
		if (!is_initialized_)
		{
			throw bad_optional_access{};
		}
		T* ptr = reinterpret_cast<T*>(data_);
		return *ptr;
	}

	const T& operator*() const&
	{
		if (!is_initialized_)
		{
			throw bad_optional_access{};
		}
		const T* ptr = reinterpret_cast<const T*>(data_);
		return *ptr;
	}

	T* operator->() { return &(**this); }

	const T* operator->() const { return &(**this); }

	T&& operator*() &&
	{
		if (!is_initialized_)
		{
			throw bad_optional_access{};
		}
		T* ptr = reinterpret_cast<T*>(data_);
		return std::move(*ptr);
	}

	T& value() &
	{
		if (!is_initialized_)
		{
			throw bad_optional_access{};
		}
		T* ptr = reinterpret_cast<T*>(data_);
		return *ptr;
	}

	const T& value() const&
	{
		if (!is_initialized_)
		{
			throw bad_optional_access{};
		}
		const T* ptr = reinterpret_cast<const T*>(data_);
		return *ptr;
	}

	template <typename... Args>
	void emplace(Args&&... args)
	{
		reset();
		new (data_) T(std::forward<Args>(args)...);
		is_initialized_ = true;
	}

	void reset()
	{
		if (is_initialized_)
		{
			reinterpret_cast<T*>(data_)->~T();
			is_initialized_ = false;
		}
	}

	~optional() { reset(); }

	bool has_value() const { return is_initialized_; };

   private:
	alignas(T) uint8_t data_[sizeof(T)];
	bool is_initialized_ = false;
};
}  // namespace bmstu