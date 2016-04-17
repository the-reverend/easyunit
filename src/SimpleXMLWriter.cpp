#include "StdAfx.h"

#include "SimpleXMLWriter.h"

namespace SimpleXMLWriter
{

	std::ostream& operator<< ( std::ostream& ostr, Element& data )
	{
		if ( data.m_comment.GetValue().size() )
		{
			ostr << data.m_Indent << data.m_comment << std::endl;
		}

		ostr << data.m_Indent << "<" << data.m_Name;

		Element::AttribContainerType::iterator iter = data.m_Attribs.begin();

		while ( iter != data.m_Attribs.end() )
		{
			if ( !iter->GetName().size() && iter->GetValue().size() )
			{
				throw TokenizerException( "Attribute value without a name" );
			}
			else
			{
				ostr << " " << iter->GetName() << " = \"" << iter->GetValue() << "\"";
			}
			iter++;
		}

		ostr << ">";

		if ( data.m_Value.size() )
		{
			ostr << data.m_Value;
		}

		Element::ElemContainerType::iterator e_iter = data.m_Elems.begin();
		if ( e_iter != data.m_Elems.end() )
		{
			ostr << std::endl;
		}

		std::string tmpIndent = INDENT_SIZE + data.m_Indent;
		while ( e_iter != data.m_Elems.end() )
		{
			if ( e_iter->GetName().size() )
			{
				e_iter->m_Indent = tmpIndent;
				ostr << *e_iter;
				ostr << std::endl;
			}
			else
			{
				throw TokenizerException( "Element without a name" );
			}

			e_iter++;
		}

		if ( data.m_Value.size() || data.m_Elems.size() )
		{
			if ( data.m_Elems.size() )
			{
				ostr << data.m_Indent << "</" << data.m_Name << ">";
			}
			else
			{
				ostr << "</" << data.m_Name << ">";
			}
		}
		else
		{
			ostr << "</" << data.m_Name << ">";
		}

		return ostr;
	}

	std::ostream& operator<< ( std::ostream& ostr, Document& data )
	{
		bool header = false;
		if ( data.m_prolog.GetValue().size() )
		{
			ostr << data.m_prolog << std::endl;
			header = true;
		}

		if ( data.m_styleSheet.GetValue().size() )
		{
			ostr << data.m_styleSheet << std::endl;
			header = true;
		}

		if ( header )
		{
			ostr << std::endl;
		}

		if ( data.m_comment.GetValue().size() )
		{
			ostr << data.m_comment << std::endl;
		}

		ostr << data.m_baseElement;

		return ostr;
	}
}