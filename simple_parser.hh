/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*! \brief Used for decode the text from the
 *         XML files. 
 *
 * Copyright (c) 2008, 2009, 2010, 2011 Ciaran McCreesh
 *
 * This file is part of the Paludis package manager. Paludis is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * Paludis is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Adapted for non-Paludis usage by H. Garcia de Marina <hgdemarina@gmail.com>
 */

#ifndef SIMPLE_PARSER_HH
#define SIMPLE_PARSER_HH 1

#include <functional>
#include <string>

namespace simple_parser
{
	typedef std::function<std::string::size_type (const std::string &,
			const std::string::size_type)> SimpleParserMatchFunction;


/*! \brief Used for decode the text from the
 *         XML files. 
 *
 * Copyright (c) 2008, 2009, 2010, 2011 Ciaran McCreesh
 *
 * This file is part of the Paludis package manager. Paludis is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * Paludis is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Adapted for non-Paludis usage by H. Garcia de Marina <hgdemarina@gmail.com>
 */
	class SimpleParserExpression
	{
		private:
			const SimpleParserMatchFunction _match;

		public:
			SimpleParserExpression(const SimpleParserMatchFunction &);

			std::string::size_type
			match(const std::string &, const std::string::size_type) const;
	};

	SimpleParserExpression operator& (const SimpleParserExpression &,
			const SimpleParserExpression &);
	SimpleParserExpression operator>> (const SimpleParserExpression &,
			std::string &);
	SimpleParserExpression operator* (const SimpleParserExpression &);
	SimpleParserExpression operator+ (const SimpleParserExpression &);
	SimpleParserExpression operator- (const SimpleParserExpression &);
	SimpleParserExpression exact(const std::string &);
	SimpleParserExpression exact_ignoring_case(const std::string &);
	SimpleParserExpression any_of(const std::string &);
	SimpleParserExpression any_except(const std::string &);

	static const std::string lc_alpha("abcdefghijklmnopqrstuvwxyz");
	static const std::string uc_alpha("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	static const std::string all_alpha(lc_alpha + uc_alpha);
	static const std::string digits("0123456789");
	static const std::string numbers(digits + "-+.e");
	static const std::string all_ws(" \t\n");
};

/*! \brief Used for decode the text from the
 *         XML files. 
 *
 * Copyright (c) 2008, 2009, 2010, 2011 Ciaran McCreesh
 *
 * This file is part of the Paludis package manager. Paludis is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * Paludis is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Adapted for non-Paludis usage by H. Garcia de Marina <hgdemarina@gmail.com>
 */

class SimpleParser
{
	private:
        std::string _text;
        std::string::size_type _offset;

	public:
		SimpleParser(const std::string &);
		~SimpleParser();

		bool consume(const simple_parser::SimpleParserExpression &);
		bool lookahead(const simple_parser::SimpleParserExpression &) const;
		bool eof() const;

		std::string::size_type offset() const;
		unsigned current_line_number() const;
		const std::string text() const;
        const std::string rest() const;
};

#endif
