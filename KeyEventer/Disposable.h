#pragma once

template<class T>
class Disposable
{
public:
	using Deleter = std::function<void(T&)>;
	using DeleterRewrapper = std::function<Deleter(Deleter&&)>;

	const T& get() const
	{
		return _value;
	}

	T& get()
	{
		return _value;
	}

	const Deleter& get_deleter() const
	{
		return _deleter;
	}

	Deleter& get_deleter()
	{
		return _deleter;
	}

	template<class T_>
	Disposable(T_&& value, const Deleter& deleter)
		: _value(std::forward<T_>(value))
		, _deleter(deleter)
	{}

	template<class T_>
	Disposable(T_&& value, Deleter&& deleter)
		: _value(std::forward<T_>(value))
		, _deleter(std::move(deleter))
	{}

	Disposable(Disposable<T>&& rhs)
		: _value(std::move(rhs._value))
		, _deleter(std::move(rhs._deleter))
	{}

	template<class DeleterRewrapper_>
	Disposable(Disposable<T>&& rhs, const DeleterRewrapper_& deleterRewrapper)
		: _value(std::move(rhs._value))
		, _deleter(deleterRewrapper(std::move(rhs._deleter)))
	{}

	Disposable(Disposable<T>&) = delete;
	Disposable() = default;
	Disposable<T>& operator=(Disposable<T>&) = delete;
	Disposable<T>& operator=(Disposable<T>&&) = default;

	~Disposable()
	{
		if(_deleter)
			_deleter(_value);
	}

private:
	Deleter _deleter = {};
	T _value = {};
};

