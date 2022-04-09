#include "buttonActions.h"

char* UpdateStr(int btnID) {
	switch (btnID)
	{
	case 0:
		return "1";
		break;
	case 1:
		return "2";
		break;
	case 2:
		return "3";
		break;
	case 6:
		return "4";
		break;
	case 7:
		return "5";
		break;
	case 8:
		return "6";
		break;
	case 12:
		return "7";
		break;
	case 13:
		return "8";
		break;
	case 14:
		return "9";
		break;
	case 19:
		return "0";
		break;
	case 18:
		return ".";
		break;
	case 3:
		return "sin(";
		break;
	case 4:
		return "cos(";
		break;
	case 5:
		return "tan(";
		break;
	case 9:
		return "+";
		break;
	case 10:
		return "-";
		break;
	case 11:
		return "/";
		break;
	case 15:
		return "*";
		break;
	case 16:
		return "^";
		break;
	case 17:
		return "sqrt(";
		break;
	case 20:
		return "(";
		break;
	case 21:
		return ")";
		break;
	default:
		return "";
		break;
	}
}

int UpdateLen(int btnID) {
	switch (btnID)
	{
	case 0:
		return 1;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 1;
		break;
	case 6:
		return 1;
		break;
	case 7:
		return 1;
		break;
	case 8:
		return 1;
		break;
	case 12:
		return 1;
		break;
	case 13:
		return 1;
		break;
	case 14:
		return 1;
		break;
	case 19:
		return 1;
		break;
	case 18:
		return 1;
		break;
	case 3:
		return 4;
		break;
	case 4:
		return 4;
		break;
	case 5:
		return 4;
		break;
	case 9:
		return 1;
		break;
	case 10:
		return 1;
		break;
	case 11:
		return 1;
		break;
	case 15:
		return 1;
		break;
	case 16:
		return 1;
		break;
	case 17:
		return 5;
		break;
	case 20:
		return 1;
		break;
	case 21:
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

//int UpdateString(char* str, int length, int btnID) {
//	switch (btnID)
//	{
//		case 0:
//			str = Merge2(str, "1", length, 2);
//			return length + 1;
//			break;
//		case 1:
//			str = Merge2(str, "2", length, 1);
//			return length + 1;
//			break;
//		case 2:
//			str = Merge2(str, "3", length, 1);
//			return length + 1;
//			break;
//		case 6:
//			str = Merge2(str, "4", length, 1);
//			return length + 1;
//			break;
//		case 7:
//			str = Merge2(str, "5", length, 1);
//			return length + 1;
//			break;
//		case 8:
//			str = Merge2(str, "6", length, 1);
//			return length + 1;
//			break;
//		case 12:
//			str = Merge2(str, "7", length, 1);
//			return length + 1;
//			break;
//		case 13:
//			str = Merge2(str, "8", length, 1);
//			return length + 1;
//			break;
//		case 14:
//			str = Merge2(str, "9", length, 1);
//			return length + 1;
//			break;
//		case 19:
//			str = Merge2(str, "0", length, 1);
//			return length + 1;
//			break;
//		case 18:
//			str = Merge2(str, ".", length, 1);
//			return length + 1;
//			break;
//		case 3:
//			str = Merge2(str, "sin(", length, 4);
//			return length + 4;
//			break;
//		case 4:
//			str = Merge2(str, "cos(", length, 4);
//			return length + 4;
//			break;
//		case 5:
//			str = Merge2(str, "tan(", length, 4);
//			return length + 4;
//			break;
//		case 9:
//			str = Merge2(str, "+", length, 1);
//			return length += 1;
//			break;
//		case 10:
//			str = Merge2(str, "-", length, 1);
//			return length + 1;
//			break;
//		case 11:
//			str = Merge2(str, "/", length, 1);
//			return length + 1;
//			break;
//		case 15:
//			str = Merge2(str, "*", length, 1);
//			return length + 1;
//			break;
//		case 16:
//			str = Merge2(str, "^", length, 1);
//			return length + 1;
//			break;
//		case 17:
//			str = Merge2(str, "sqrt(", length, 5);
//			return length + 5;
//			break;
//		case 20:
//			str = Merge2(str, "(", length, 1);
//			return length + 1;
//			break;
//		case 21:
//			str = Merge2(str, ")", length, 1);
//			return length + 1;
//			break;
//		case 22:
//			if (length > 0) {
//				str = Substr(str, 0, length - 1);
//				return length - 1;
//			}
//			else {
//				return length;
//			}
//			break;
//		default:
//			return length;
//			break;
//	}
//}