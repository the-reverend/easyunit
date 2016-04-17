
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>


namespace SimpleXMLWriter
{

	class TokenizerException : public std::exception
	{
	public:
		TokenizerException( const std::string& what )
				: std::exception( what.c_str() )
		{}
	};

#define INDENT_SIZE "  "
#define DEFAULT_SIZE 32
	class Element;

	class Attrib
	{
	public:
		Attrib( const std::string& name )
				: m_Value()
		{
			m_Name = name;
		}

		Attrib( const std::string& name, const std::string& value )
				: m_Name( name )
				, m_Value( value )
		{
		}

		Attrib( const std::string& name, int value )
				: m_Name( name )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%d", value );
			m_Value = buffer;
		}

		Attrib( const std::string& name, long value )
				: m_Name( name )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%ld", value );
			m_Value = buffer;
		}

		Attrib( const std::string& name, double value )
				: m_Name( name )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%lf", value );
			m_Value = buffer;
		}

		Attrib& SetName( const std::string& name )
		{
			m_Name = name;
			return *this;
		}

		Attrib& SetValue( const std::string& value )
		{
			m_Value = value;

			return *this;
		}

		Attrib& SetValue( int value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%d", value );
			m_Value = buffer;

			return *this;
		}

		Attrib& SetValue( long value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%ld", value );
			m_Value = buffer;

			return *this;
		}

		Attrib& SetValue( double value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%lf", value );
			m_Value = buffer;

			return *this;
		}

		Attrib& operator=( const std::string& value )
		{
			m_Value = value;

			return *this;
		}

		Attrib& operator=( int value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%d", value );
			m_Value = buffer;

			return *this;
		}

		Attrib& operator=( long value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%ld", value );
			m_Value = buffer;

			return *this;
		}

		Attrib& operator=( double value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%lf", value );
			m_Value = buffer;

			return *this;
		}

		Attrib& operator=( const Attrib& attrib )
		{
			m_Name = attrib.m_Name;
			m_Value = attrib.m_Value;
			return *this;
		}

		std::string& GetValue()
		{
			return m_Value;
		}

		std::string& GetName()
		{
			return m_Name;
		}

	private:
		std::string m_Name;
		std::string m_Value;

		friend std::ostream& operator<< ( std::ostream& ostr, Attrib& attr );
	};

	inline std::ostream& operator<< ( std::ostream& ostr, Attrib& attr )
	{
		ostr << "'" << attr.m_Name << " = " << attr.m_Value << "'";
		return ostr;
	}

	class Prolog
	{
	public:
		Prolog( const std::string& value )
		{
			m_Value = value;
		}

		std::string& GetValue()
		{
			return m_Value;
		}

	private:
		std::string m_Value;

		friend std::ostream& operator<< ( std::ostream& ostr, const Prolog& data );
	};

	inline std::ostream& operator<< ( std::ostream& ostr, const Prolog& data )
	{
		ostr << "<?" << data.m_Value << "?>";
		return ostr;
	}

	class StyleSheet
	{
	public:
		StyleSheet( const std::string& value )
		{
			m_Value = value;
		}

		std::string& GetValue()
		{
			return m_Value;
		}

	private:
		std::string m_Value;

		friend std::ostream& operator<< ( std::ostream& ostr, const StyleSheet& data );
	};

	inline std::ostream& operator<< ( std::ostream& ostr, const StyleSheet& data )
	{
		ostr << "<?" << data.m_Value << "?>";
		return ostr;
	}

	class Comment
	{
	public:
		Comment( const std::string& value )
		{
			m_Value = value;
		}

		std::string& GetValue()
		{
			return m_Value;
		}

	private:
		std::string m_Value;

		friend std::ostream& operator<< ( std::ostream& ostr, Comment& data );
	};

	inline std::ostream& operator<< ( std::ostream& ostr, Comment& data )
	{
		ostr << "<!-- " << data.m_Value << " -->";
		return ostr;
	}

	class Element
	{
	public:
		typedef std::vector<Attrib> AttribContainerType;
		typedef std::vector<Element> ElemContainerType;

		Element( const std::string& name )
				: m_Name( name )
				, m_Attribs()
				, m_Elems()
				, m_comment( "" )
				, m_Indent( "" )
		{
		}

		Element( const std::string& name, const std::string& value )
				: m_Name( name )
				, m_Value( value )
				, m_Attribs()
				, m_Elems()
				, m_comment( "" )
				, m_Indent( "" )
		{
		}

		// The element's name is not changed
		Element& Clear()
		{
			m_Attribs.clear();
			m_Elems.clear();
			m_Value.clear();
			m_comment.GetValue().clear();
			return *this;
		}

		std::string& GetName()
		{
			return m_Name;
		}

		Element& operator= ( const Comment& comment )
		{
			m_comment = comment;
			return *this;
		}

		Element& AddComment( const std::string& comment )
		{
			m_comment = comment;
			return *this;
		}

		Element& operator+= ( const Attrib& token )
		{
			m_Attribs.push_back( token );
			return *this;
		}

		Element& Add( const Attrib& token )
		{
			m_Attribs.push_back( token );
			return *this;
		}

		Element& operator<< ( const Attrib& token )
		{
			m_Attribs.push_back( token );
			return *this;
		}

		Element& operator+= ( const Element& token )
		{
			m_Elems.push_back( token );
			return *this;
		}

		Element& Add( const Element& token )
		{
			m_Elems.push_back( token );
			return *this;
		}

		Element& operator<< ( const Element& token )
		{
			m_Elems.push_back( token );
			return *this;
		}

		Element& operator=( const std::string& value )
		{
			m_Value = value;

			return *this;
		}

		Element& operator=( int value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%d", value );
			m_Value = buffer;

			return *this;
		}

		Element& operator=( long value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%ld", value );
			m_Value = buffer;

			return *this;
		}

		Element& operator=( double value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%lf", value );
			m_Value = buffer;

			return *this;
		}

		Element& SetValue( const std::string& value )
		{
			m_Value = value;

			return *this;
		}

		Element& SetValue( int value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%d", value );
			m_Value = buffer;

			return *this;
		}

		Element& SetValue( long value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%ld", value );
			m_Value = buffer;

			return *this;
		}

		Element& SetValue( double value )
		{
			char buffer [DEFAULT_SIZE];
			sprintf_s( buffer, DEFAULT_SIZE, "%lf", value );
			m_Value = buffer;

			return *this;
		}

	private:
		Comment m_comment;
		std::string m_Name;
		std::string m_Value;
		AttribContainerType m_Attribs;
		ElemContainerType m_Elems;
		std::string m_Indent;

		friend std::ostream& operator<< ( std::ostream& ostr, Element& data );
	};

	std::ostream& operator<< ( std::ostream& ostr, Element& data );

	class Document
	{
	public:
		Document()
				: m_prolog( "" )
				, m_comment( "" )
				, m_styleSheet( "" )
				, m_baseElement( "" )
		{
		}

		Document& operator= ( const Prolog& prolog )
		{
			m_prolog = prolog;
			return *this;
		}

		Document& AddProlog( const std::string& prolog )
		{
			m_prolog = prolog;
			return *this;
		}

		Document& operator= ( const StyleSheet& ss )
		{
			m_styleSheet = ss;
			return *this;
		}

		Document& AddStyleSheet( const std::string& ss )
		{
			m_styleSheet = ss;
			return *this;
		}

		Document& operator= ( const Comment& comment )
		{
			m_comment = comment;
			return *this;
		}

		Document& AddComment( const std::string& comment )
		{
			m_comment = comment;
			return *this;
		}

		Document& operator= ( const Element& token )
		{
			m_baseElement = token;
			return *this;
		}

		Document& AddBaseElem( const Element& token )
		{
			m_baseElement = token;
			return *this;
		}

		Document& operator<< ( const Element& token )
		{
			m_baseElement = token;
			return *this;
		}
	private:
		Prolog m_prolog;
		StyleSheet m_styleSheet;
		Comment m_comment;
		Element m_baseElement;

		friend std::ostream& operator<< ( std::ostream& ostr, Document& data );
	};

	std::ostream& operator<< ( std::ostream& ostr, Document& data );
}