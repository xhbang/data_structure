ǳ̸��׺���ʽ����ֵ

����֪����׺���ʽ����ֵ,ͨ��������ת��Ϊ��׺���ʽ,��ͨ����ջ�����׺���ʽ��ֵ���������,����в�̫�������μ���
http://202.113.89.254/DataStructure/DS/web/zhanhuoduilie/zhanhuoduilie3.3.1.htm��ԭ��
http://tech.ccw.com.cn/article/252014.htm��ʵ�֣�
 
����ChinaDHF����ƪ����׺���ʽ���沨�����ʽ��ת������ֵ��д�ĺ����,����û�жԷ��Ŵ���,��û�жԲ�����������жϡ�������,������������ô������������ƪ���¡�
������ChinaDHF�Ĵ���Ľṹ��
1.����׺���ʽ�����﷨��������ƺϷ��Լ�顣
    2.����׺���ʽת��Ϊ�沨�����ʽ��
    3.�����沨�����õ�������Ҫ��ֵ��
 
�����վ�,���ȼ��Ϸ��ԡ�
Ϊ�˷�����������,������Ҫ��һ���滻,������ֻ�����ַ�����ʾ���������,���滻��һ���ַ�(char)����ʽ��
private static string ReplaceExpString(string ExpString) {
            //����ı��ʽֱ�Ӳ��õ���C�ķ��,��ζ�����ע�͵�
            ExpString = ExpString.Replace("NOT", "!");
            ExpString = ExpString.Replace("OR", "|");
            ExpString = ExpString.Replace("AND", "&");
                 //��˫�ֵ������ת���������Ǵ���
            ExpString = ExpString.Replace(">=", ((char)242).ToString());//��������ʾ���ڵ���
            ExpString = ExpString.Replace("<=", ((char)243).ToString());//��������ʾС�ڵ���
            ExpString = ExpString.Replace("<>", ((char)247).ToString());//���¡���ʾ������
            ExpString = Regex.Replace ( ExpString, @"\s+", "" );//�������еĿո�
            return ExpString;
        }
public static string RexStringWord = @"[#&|!+=<>.- *()/�¨���]";
public static string RexStringNumber = @"-?(\d+\.?\d*)";
public static string RexStringLining = @"[(]#[+\-*><=&|�¨���]+#[)]";
public static string RexStringExp = @��([#][+\-*><=&|�¨���])+[#] ";

�ںϷ��Լ������,���ǰ����е�����(������,��������,��С��,����С��)��������ʽRexStringNumber���滻��#��
�滻����ʽ�����ֻ�������ơ� #+#-# ��,�� #*(#-#) ��,��(#<#)�� �ȵȵ��ˡ�����������ʽRexStringLining�滻�����д����ŵ�,�����RexStringExp�滻���������ŵ�,�������ʣ�µ�ֻ����#��
public static bool IsRight ( string expString ) {
            string ExpString = ReplaceExpString ( expString );
            ExpString = Regex.Replace ( ExpString, RexStringNumber, "#" );//�滻��������
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
�����Ѿ�����˺Ϸ��Եļ��,�ܼ�,ֻ����չ�Ҽ����������Ȼ������������ת����׺���ʽ�����⡣ת����׺���ʽ�м���������Ҫ��һ��,����ChinaDHF��ʵ��,��ֻ�����˴�2Ԫ�������Ҳ����˵�����ڷ���,��,��û�а취��������������Ҫ���һ���ܹ�����һԪ������Ĵ���Ρ��ڶ��㣬���ڡ�-�������Ǹ���,���Ǽ���,������Ҫһ���ж�,ʲôʱ���Ǹ��ţ�ʲôʱ���Ǽ��š�
����֪��,һ����˵�������-���ų����ڱ��ʽ�ʼ,�����������������(-#),��ô��һ���Ǹ���,���������-���ų����������š�(�����棬������������֣���-#����ô��Ҳһ���Ǹ���,����������λ�õġ�-����,���Ƕ����������Ŵ����ˡ�Ϊ��������ź͸���,�ҰѸ���(1Ԫ�����)���滻������һ������,���������á�\����
�������ϵ�˼·,�����������һ���������Ѹ����滻�ɡ�\����
private string ReplaceMinusString(string expString) {
            string rstr = expString;
            //�������ַ�Ϊ-,����Ϊ���ֵ�ƥ��
            if(Regex.IsMatch(rstr,@"\A-(\d+\.?\d*)")){
                rstr = rstr.Remove(0,1);
                rstr = "\\" + rstr;
            }
            //�����ԣ�-��ʼ����Ϊ���ֵ�ƥ��
            while (Regex.IsMatch(rstr, @"\(-(\d+\.?\d*)")) {
                foreach (Match m in Regex.Matches(rstr, RexMinusString)) {
                    int index = m.Index + 1;
                    rstr = rstr.Remove(index, 1);
                    rstr = rstr.Insert(index, "\\");
                }
            }
            return rstr;
        }

����ĺ�������˸���ת����\���Ĺ�����
public static string GetRnpExpValue ( string exp ) {
              string strexp = ReplaceExpString(exp);//���������
            strexp = ReplaceMinusString(strexp);//�����滻
            string strRnpExp = string.Empty;
            string num = string.Empty;
            Stack<char> stack = new Stack<char> ( );
            string strexp;
            for ( int i = 0; i < strexp.Length; i++ ) {
                if ( char.IsDigit ( strexp[i] ) || strexp[i] == '.' )
                    num += strexp[i];
               else if ( "\\,!+-*/><=&|�¨���".IndexOf ( strexp[i] ) >= 0 ) {
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
 
����������ȼ��Ƚϣ�����ͳһ����char����������,����ǰ�����������ĵ��ַ�ת��
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

���ϰ���׺���ʽת���ɺ�׺���ʽ�ĺ�����ChinaDHF��һ��,ֻ��,ǰ�����2�������Ĵ�������ж��㷨�����,��㿪ƪ��ԭ�����ӡ�
ͨ������Ĵ���,�����Ѿ����԰�һ���Ϸ�����׺���ʽת�����˺�׺���ʽ,��ô������ô����ô������ô���ܴ���һԪ������أ��ں�׺���ʽ��ֵ���㷨����,������+-*/ʱ������2����ջ����ȡ��2��������,�����������һ���ж�����һԪ���������ֻ��ȡһ����������
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
                //һԪ������ĵ����ж�
                else if ( c == '!' || c=='\\') {
                    string v = stack.Pop ( );
                    result = Opert ( v, "", c );
                    stack.Push ( result );
                }
            }
            return result;
        }

���������ֵ��,�������󲼶�ֵ,������������,���������������,�м�û�м��쳣����,������� ����ֵ �� ����������������,����δ�������Ȥ�Ŀ����ٸĸġ�

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

������Щ,������һ�����޸�,����һ��,������������ֻ�������IF�������,�������Ұ�IF�Ĵ���ȥ���ˣ�IF����ܼ򵥵�,��������䵥�������,�ж�,�����true��ִ��THEN��,����ִ��ELSE��
�Ҿ�����������ʽд�Ĳ���,�㷨��Ҳ�в��õĵط�,ϣ������ָ�̡�