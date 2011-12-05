浅谈中缀表达式的求值

我们知道中缀表达式的求值,通常都是先转换为后缀表达式,在通过堆栈求出后缀表达式的值，对于这点,如果有不太清楚的请参见：
http://202.113.89.254/DataStructure/DS/web/zhanhuoduilie/zhanhuoduilie3.3.1.htm（原理）
http://tech.ccw.com.cn/article/252014.htm（实现）
 
对于ChinaDHF的这篇“中缀表达式到逆波兰表达式的转换及求值”写的很清楚,但他没有对符号处理,更没有对布尔运算进行判断。在这里,我们来看看怎么来完善他的这篇文章。
下面是ChinaDHF的代码的结构。
1.对中缀表达式进行语法分析，或称合法性检查。
    2.将中缀表达式转换为逆波兰表达式。
    3.计算逆波兰表达得到我们想要的值。
 
我们照久,首先检查合法性。
为了方便后面的运算,我们先要做一个替换,把所有只能用字符串表示的运算符号,都替换成一个字符(char)的形式。
private static string ReplaceExpString(string ExpString) {
            //如果改表达式直接采用的是C的风格,这段都可以注释掉
            ExpString = ExpString.Replace("NOT", "!");
            ExpString = ExpString.Replace("OR", "|");
            ExpString = ExpString.Replace("AND", "&");
                 //把双字的运算符转化方便我们处理
            ExpString = ExpString.Replace(">=", ((char)242).ToString());//‘ò’表示大于等于
            ExpString = ExpString.Replace("<=", ((char)243).ToString());//‘ó’表示小于等于
            ExpString = ExpString.Replace("<>", ((char)247).ToString());//‘÷’表示不等于
            ExpString = Regex.Replace ( ExpString, @"\s+", "" );//消除所有的空格
            return ExpString;
        }
public static string RexStringWord = @"[#&|!+=<>.- *()/÷òó]";
public static string RexStringNumber = @"-?(\d+\.?\d*)";
public static string RexStringLining = @"[(]#[+\-*><=&|÷òó]+#[)]";
public static string RexStringExp = @”([#][+\-*><=&|÷òó])+[#] ";

在合法性检查里面,我们把所有的数字(带负号,不带负号,带小数,不带小数)用正则表达式RexStringNumber都替换成#号
替换后表达式里面就只存在类似” #+#-# “,” #*(#-#) “,”(#<#)” 等等的了。在用正则表达式RexStringLining替换掉所有带括号的,最后用RexStringExp替换掉不带括号的,于是最后剩下的只会是#号
public static bool IsRight ( string expString ) {
            string ExpString = ReplaceExpString ( expString );
            ExpString = Regex.Replace ( ExpString, RexStringNumber, "#" );//替换所有数字
            if ( Regex.Matches ( ExpString, RexStringWord ).Count > 0 ) {
                while ( Regex.IsMatch ( p, RexStringLining ) ) {
                foreach ( Match match in Regex.Matches (ExpString, RexStringLining ) ) {
                    string strsingle = match.Value.Substring ( 1, match.Value.Length - 2 );
                    if ( !Regex.IsMatch ( strsingle, RexStringExp ) )
return false; 
}
                ExpString = Regex.Replace (ExpString, RexStringLining, "#" );
            }
            if ( p == "#" ) return true;
            if ( !Regex.IsMatch ( p, RexStringExp ) ) return false;
                 else return true;
}
我们已经完成了合法性的检查,很简单,只是扩展我几个运算符。然后我们来看看转换后缀表达式的问题。转换后缀表达式有几个问题先要提一下,对于ChinaDHF的实现,他只处理了带2元运算符，也就是说，对于符号,非,他没有办法做到。首先我们要设计一个能够处理一元运算符的代码段。第二点，对于”-“他既是负号,又是减号,我们需要一个判断,什么时候是负号，什么时候是减号。
我们知道,一般来说，如果’-‘号出现在表达式最开始,而后面紧跟的是数字(-#),那么他一定是负号,另外如果’-‘号出现在左括号’(‘后面，而后面紧跟数字（（-#）那么他也一定是负号,而对于其他位置的’-‘号,我们都把他做减号处理了。为了区别减号和负号,我把负号(1元运算符)都替换成另外一个符号,在这里我用’\’。
有了以上的思路,我们先来设计一个函数，把负号替换成’\’。
private string ReplaceMinusString(string expString) {
            string rstr = expString;
            //查找首字符为-,后面为数字的匹配
            if(Regex.IsMatch(rstr,@"\A-(\d+\.?\d*)")){
                rstr = rstr.Remove(0,1);
                rstr = "\\" + rstr;
            }
            //查找以（-开始后面为数字的匹配
            while (Regex.IsMatch(rstr, @"\(-(\d+\.?\d*)")) {
                foreach (Match m in Regex.Matches(rstr, RexMinusString)) {
                    int index = m.Index + 1;
                    rstr = rstr.Remove(index, 1);
                    rstr = rstr.Insert(index, "\\");
                }
            }
            return rstr;
        }

上面的函数完成了负号转换’\’的工作。
public static string GetRnpExpValue ( string exp ) {
              string strexp = ReplaceExpString(exp);//运算符化减
            strexp = ReplaceMinusString(strexp);//负号替换
            string strRnpExp = string.Empty;
            string num = string.Empty;
            Stack<char> stack = new Stack<char> ( );
            string strexp;
            for ( int i = 0; i < strexp.Length; i++ ) {
                if ( char.IsDigit ( strexp[i] ) || strexp[i] == '.' )
                    num += strexp[i];
               else if ( "\\,!+-*/><=&|÷òó".IndexOf ( strexp[i] ) >= 0 ) {
                    if ( num.Length > 0 ) {
                        strRnpExp += "[" + num + "]";
                        num = string.Empty;
                    }
                    while ( stack.Count > 0 ) {
                        char opInStack = (char)stack.Pop ( );
                        if ( opInStack == '(' || Power ( opInStack ) < Power ( strexp[i] ) ) {
                            stack.Push ( opInStack );
                            break;
                        }
                        else strRnpExp += opInStack;
                    }
                    stack.Push ( strexp[i] );
                }
                else if ( strexp[i] == '(' )
                    stack.Push ( strexp[i] );
                if ( strexp[i] == ')' ) {
                    if ( num.Length > 0 ) {
                        strRnpExp += "[" + num + "]";
                        num = string.Empty;
                    }
                    while ( stack.Count > 0 ) {
                        char opInStack = (char)stack.Pop ( );
                        if ( opInStack == '(' ) break;
                        else strRnpExp += opInStack;
                    }
                }
            }
            if ( num.Length > 0 ) {
                strRnpExp += "[" + num + "]";
                num = string.Empty;
            }
            while ( stack.Count > 0 )
                strRnpExp += stack.Pop ( );
            strRnpExp = Regex.Replace ( strRnpExp, ",", "" );
            return strRnpExp;
        }
 
运算符的优先级比较：这里统一采用char类型做参数,所有前面出现运算符的单字符转化
private static int Power ( char o ) {
            switch ( o ) {
                case '+':
                case '-':
                    return 1;
                case '*':
                case '/':
                    return 2;
                case '\\':
                case '!':
                    return 3;
                    
                default:
                    return 0;
            }
        }

以上把中缀表达式转换成后缀表达式的函数和ChinaDHF的一样,只是,前面多了2个函数的处理。如果有对算法不清楚,请点开篇的原理连接。
通过上面的处理,我们已经可以把一个合法的中缀表达式转换成了后缀表达式,那么我们怎么，那么我们怎么才能处理一元运算符呢？在后缀表达式求值的算法里面,在遇到+-*/时都会有2次退栈，提取出2个操作数,我在这里加了一个判断遇到一元运算符，就只提取一个操作数。
public static string GetValueByRpn ( string rpnExp ) {
            Stack<string> stack = new Stack<string> ( );
            char[] expChar = rpnExp.ToCharArray ( );
            string digit = string.Empty;
            string result = "0";
            for ( int i = 0; i < expChar.Length; i++ ) {
                char c = expChar[i];
                if ( c == '[' ) {
                    digit = string.Empty;
                }
                else if ( c == ']' ) {
                    stack.Push ( digit );
                }
                else if ( char.IsDigit ( c ) || c == '.' ) {
                    digit += c.ToString ( );
                }
                else if ( c == '+' || c == '-' || c == '*' || c == '/' || c == '>' || c == '<' || c == (char)242 || c == (char)243 || c == (char)247 || c == '&' || c == '|' || c == '=' ) {
                    string v2 = stack.Pop ( );
                    string v1 = stack.Pop ( );
                    result = Opert ( v1, v2, c );
                    stack.Push ( result );
                }
                //一元运算符的单独判断
                else if ( c == '!' || c=='\\') {
                    string v = stack.Pop ( );
                    result = Opert ( v, "", c );
                    stack.Push ( result );
                }
            }
            return result;
        }

这里便是求值了,无论是求布尔值,还是四则运算,都是这个函数处理,中间没有加异常处理,如果遇到 布尔值 与 浮点数的运算会出错,对这段代码有兴趣的可以再改改。

private static string Opert ( string v1, string v2, char o ) {
            switch ( o ) {
                case '+':
                    return ( Convert.ToDouble ( v1 ) + Convert.ToDouble ( v2 ) ).ToString ( );
                case '-':
                    return ( Convert.ToDouble ( v1 ) - Convert.ToDouble ( v2 ) ).ToString ( );
                case '*':
                    return ( Convert.ToDouble ( v1 ) * Convert.ToDouble ( v2 ) ).ToString ( );
                case '/':
                    return ( Convert.ToDouble ( v1 ) / Convert.ToDouble ( v2 ) ).ToString ( );
                case '>':
                    return ( Convert.ToDouble ( v1 ) > Convert.ToDouble ( v2 ) ).ToString ( );
                case '<':
                    return ( Convert.ToDouble ( v1 ) < Convert.ToDouble ( v2 ) ).ToString ( );
                case '=':
                    return ( v1 == v2 ).ToString ( );
                case (char)242://>=
                    return ( Convert.ToDouble ( v1 ) >= Convert.ToDouble ( v2 ) ).ToString ( );
                case (char)243://<=
                    return ( Convert.ToDouble ( v1 ) <= Convert.ToDouble ( v2 ) ).ToString ( );
                case (char)247://<>
                    return ( Convert.ToDouble ( v1 ) != Convert.ToDouble ( v2 ) ).ToString ( );
                case '&':
                    return ( Convert.ToBoolean ( v1 ) && Convert.ToBoolean ( v2 ) ).ToString ( );
                case '|':
                    return ( Convert.ToBoolean ( v1 ) || Convert.ToBoolean ( v2 ) ).ToString ( );
                case '!':
                    return ( !Convert.ToBoolean ( v1 ) ).ToString ( );
                case '\\':
                    return ( -Convert.ToDouble ( v1 ) ).ToString ( );
                default:
                    return null;
            }
        }

上面这些,我做了一定的修改,简化了一下,本来布尔运算只会出现在IF语句里面,在这里我把IF的处理去掉了，IF处理很简单的,把条件语句单独提出来,判断,如果是true就执行THEN块,否则执行ELSE块
我觉得我正则表达式写的不好,算法上也有不好的地方,希望高手指教。