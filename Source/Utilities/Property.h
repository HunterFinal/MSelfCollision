/*										 Property									*/
// ------------------------------------------------------------------------------------
// File name			:Property.h
// Summary				:C# like Property
// List					:1.SimpleWriteableProperty
//						 2.SimpleReadonlyProperty
// Writer				:MAI ZHICONG(バク チソウ)
// Update Message		:2024/04/30		Create(unfinished)
//						
// ------------------------------------------------------------------------------------

#pragma once

#include <iostream>

namespace MUtil
{
	template<typename T>
	class Property
	{
	public:
		Property(T& value) : _value(value) {}
		Property(const Property<T>& ref) : _value(ref._value) {}
		virtual ~Property() {}

		Property<T>& operator = (const Property<T>& ref)
		{
			this->_value = ref._value;
			return *this;
		}

	protected:
		T& _value;
	};

	template<typename T>
	class Getter
	{
	protected:
		virtual const T& Get() const = 0;
	};

	template<typename T>
	class Setter
	{
	protected:
		virtual void Set(const T& value) = 0;
	};

	template<typename T>
	class SimpleWriteableProperty : public Property<T>, private Getter<T>, private Setter<T>
	{
	public:
		SimpleWriteableProperty(T& value) : Property<T>(value) { }
		SimpleWriteableProperty(const SimpleWriteableProperty<T>& ref) : Property<T>(ref) {}
		virtual ~SimpleWriteableProperty() {}

	public:
		operator const T& () const
		{
			return this->Get();
		}
		const T& operator -> () const 
		{
			return this->Get();
		}

		SimpleWriteableProperty<T>& operator = (const T& val)
		{
			this->Set(val);

			return *this;
		}
	private:
		const T& Get() const override
		{
			return this->_value;
		}

		void Set(const T& value) override
		{
			this->_value = value;
		}
	};

	template<typename T>
	class SimpleReadonlyProperty : public Property<T>, private Getter<T>
	{
	public:
		SimpleReadonlyProperty(T& value) : Property<T>(value) { }
		SimpleReadonlyProperty(const SimpleReadonlyProperty<T>& ref) : Property<T>(ref) {}
		virtual ~SimpleReadonlyProperty() {}

	public:
		operator const T& () const
		{
			return this->Get();
		}
		const T& operator -> () const
		{
			return this->Get();
		}

	private:
		const T& Get() const override
		{
			return this->_value;
		}

	};

}// namespace MUtil
