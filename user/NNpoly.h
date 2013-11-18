#ifndef NNPOLY_H
#define NNPOLY_H
#include<iostream>
namespace antok {

	namespace user {

		namespace hubers {

			namespace NNpoly
			{
				double params[21*21] = {
					190.3381858934484,-2.7541252507155,0.4612815805170,4.0024224042747,
					19.9701469383641,-0.8006388238867,35.5553967055372,55.3575445431820,
					66.8360530317516,-143.9163654596582,41.7537855979229,110.5977110434782,
					46.5450913161373,8.0538503508639,-256.7983903019683,-0.0778300629345,
					-0.0854937932617,-0.0038243156826,-0.0667223687502,0.0089047535040,
					0.1039939370689,-0.4412610933764,-0.9020792461599,-1.1630119492713,
					6.6622009144213,25.2147052849691,-0.4396442703963,11.0363868129164,
					55.4340546355752,53.8853695251257,-96.1365229429994,-6.4834585111388,
					9.8485244804305,-39.1970813275939,-34.7390248281161,-162.8043389094993,
					-0.0947185655081,-0.1787727975744,-0.0875374295809,-0.2352403864926,
					0.0052598939506,-0.0061806188505,-1.3547384463820,4.3226631619571,
					11.0753485078061,21.8226565283623,67.4161388350635,21.9105999475521,
					-2.3239907939216,6.4055236758455,207.5877493053056,-0.7578639250198,
					-152.8766727317255,15.7796817210891,-174.9840630451316,313.6019332686844,
					-1.1951232443940,-0.0326590927753,-0.1751782520164,-0.1307295503462,
					-0.0762365017188,0.0941591163477,0.0209811747352,0.1038290943939,
					3.4739701405119,17.3617903050464,4.2042367103525,26.0049205653382,
					101.8703553546509,-11.7589286601976,-0.8192429637932,-2.9674201858069,
					147.4917075708505,-12.5894327559542,-31.4875402209497,-82.6392043011598,
					-39.9887500935579,2.7259404726241,-0.1227731815588,-0.1736732467693,
					-0.0299153854338,-0.2650672876112,0.0824733695605,-0.0138417225039,
					-0.3291346711483,3.8132916460775,7.9180965032975,-10.4342120969093,
					-35.6807211299945,0.6194590509487,-5.6983084788366,-231.8935906354710,
					-333.0942419339368,-55.6072269070528,108.0719688895408,-45.0239839754442,
					-574.9796764933174,-384.9997542050799,-29.6558649002747,0.0278852321132,
					-0.0807626440096,-0.1178341799169,-0.0384122078376,0.0444687406096,
					0.0329308778168,0.8143975152227,6.1030414993373,-0.0777469847555,
					-9.2617000747512,-1.3266867107418,-15.1854457009589,-43.5258016196321,
					-112.2782574800002,-42.7265569529572,-4.2568592790361,68.8619484984551,
					-286.9094210949790,-25.0836687760828,-18.3090987544206,-8.2521517616761,
					0.0001910256878,0.0107872208900,-0.0338622167234,-0.1646222135262,
					-0.1152531974637,-0.1920508665234,-0.1510068781438,0.1237714425501,
					-0.0996518558207,-0.5954777756974,-0.5773890983348,-11.7839265179693,
					-5.8668527136218,-11.2368277625903,-41.6016375882140,-14.8533416107157,
					-4.4050288302723,-24.3893929075102,-29.0379233439592,-4.3747475415103,
					-2.6750332774039,-0.1916578147985,-0.2235994128862,-0.0635127444536,
					-0.5506007077586,0.0424670935721,0.2426296132912,0.1112974836471,
					2.7203937385881,3.2384640596299,-4.0745176417415,-2.2724522526100,
					0.5830047596845,-7.8170007461191,-56.4042324349107,-81.8429560777431,
					3.3019219713637,-10.9002178565504,-21.3201884549111,-120.4595648970458,
					-177.8330405210561,64.5600742897304,0.0317538395435,-0.1610842180538,
					-0.1134045910128,0.0013773053703,0.3258928951967,22.0889561344883,
					0.7414478547984,-0.0626196984130,-0.2610992897802,-7.5084929444576,
					-49.0887748895103,-15.4028412365573,-5.2256156304805,-151.7007007984437,
					-72.3007252655166,-5.2114903537348,-7.9875278976119,-15.1236729765018,
					-8.0560852570210,-7.6418685990546,-4.1036439937755,0.0231041186258,
					-0.0002402952899,-0.0554967176210,-0.6963269111769,-0.0297807643246,
					-0.0595767621173,0.5309432286028,-2.8079237134820,-6.5773014416069,
					-6.7785594390852,-37.7863194477128,-1.7857830793099,22.3119640082546,
					8.7739538585197,-16.5104852157380,-17.9221471588825,163.1120703393406,
					8.2876121206511,23.7750872103259,-28.9927330882323,-4.7309051097296,
					0.0238437114886,-0.0383680784546,0.0474900333070,-0.0371073034450,
					0.4051017385553,0.9026873264114,-0.4835944335872,-1.5613496329836,
					-12.3255837065497,-6.3688767789518,-2.8988084156548,-69.7861086484740,
					-0.7155226737119,-5.0108347369537,-7.7999251804899,-101.3494896263975,
					4.4490624541319,16.1854800971971,-11.8154434939447,-4.8042087636613,
					-1.5354018131367,-0.3096636810642,-0.2345957416311,-0.0029642062624,
					-0.9119979732147,0.1705903886194,0.7172912966153,0.1492684297741,
					-0.0388475403879,-0.0139442396460,-2.2461589017903,-2.6055536322508,
					1.8921726564332,-1.5741904162210,-30.4868840150899,-17.3870376835666,
					9.6319113978895,-16.5655310723651,-12.3438561331795,-110.4075757319068,
					-34.9308569907458,1.9517060933973,-0.0346526124345,-0.1447642983405,
					-0.1445111987993,-0.0361966692486,0.4483669251441,0.1973360303187,
					0.1854520244543,-0.4985194432865,-6.0792006884147,-2.2307833149115,
					-1.1221012892155,-16.8527225784325,-1.6685340439342,-4.6593660968763,
					204.4734044942698,-4.9941687585500,-16.8916362059100,205.8714877237757,
					-8.9530654315545,466.9739064887164,-7.9859149245051,-0.0030816156079,
					0.0353477841289,-0.0220535494045,-0.7087433364681,-0.0238585501894,
					0.3066029864027,0.6978667790030,-0.6136567684086,-0.8257359487322,
					13.4208365938733,70.3154555018553,0.7908716205768,20.7966593809804,
					79.5046360321226,437.8325699073820,11.9588354851123,-21.4022841116641,
					53.2976392330035,36.9605369555396,610.8151970232806,4.8698579341860,
					0.1711157640516,0.0085415567381,0.0453206006939,-0.0695969801102,
					0.1545156102088,0.5355679760299,-0.2515773643205,-4.0540580857926,
					-0.0743016334530,6.5242724480236,-0.6607899608041,27.7519174753985,
					30.3369474232497,35.9354366418908,-4.3470642595844,142.1441891766371,
					-34.9130959993629,105.5910686951069,55.6637355073057,-6.6462494256865,
					143.9036262385928,0.0410454158309,0.1018735831072,0.1012952522193,
					-0.2376681970572,-0.2147234994641,0.1819611212447,-0.0121813671613,
					-0.0140245334052,-0.2832070651965,0.4113667384428,-0.1465350998323,
					0.4603572283252,-5.8504278949712,13.0390251762097,-0.1353157060091,
					-0.3422855281981,-0.0026018419594,-0.3160898728824,1.5271025835215,
					-0.2414891261255,-0.0534920705694,-0.7031810364015,-0.3061015619180,
					-0.0137344533027,-23.9184989249324,0.1403919542614,0.1070544241122,
					0.0666949718211,2.8868142564218,0.3265684874973,-0.2906802449117,
					14.6040913435808,-0.1634242173823,-0.6362580544415,0.1665677279527,
					0.8726875278330,-1.1287187983195,0.6961463253640,3.2475338313869,
					-0.0385722464889,-1.3371370207812,-0.9770200638465,-0.0380132628432,
					-0.2345690429370,-0.1056943260665,0.0437529735475,1.1534487961692,
					13.1642058206733,0.0393630226843,-0.2051111414687,0.7088178750113,
					-16.5229975564898,1.1841641501616,8.5404007706854,0.2379071586677,
					3.6291105812702,2.5369283997187,0.2267608932717,-0.5325384177657,
					-0.8984226305532,2.5934327347825,-0.5907499112311,-0.5043098366672,
					0.0812440897642,0.1549552193647,0.0512997695145,-1.4608928811903,
					0.0561174015109,0.4395536921246,0.0477368479194,-0.3810677755784,
					-0.0195897038944,0.0948640488693,1.3116337269196,-0.1358047866535,
					40.0148072944298,0.8051784829338,0.8321791045593,-0.2591567186596,
					-0.3571129202561,-0.1434750244525,-0.3363455820667,-1.0532302494611,
					-0.0154282352998,0.2463137094023,0.0153910396120,0.1495944902068,
					0.0506264371268,0.7046277395690,0.7979805066152,0.1531442399776,
					-0.0708869841019,0.0647501958977,0.1196557659991,2.6988703558112,
					-0.0597559358029,-1.2433431303499,0.1919545489493,0.8998211632869,
					-0.0833870198858,-0.4340222140671,-1.2978625375607,1.5894034035671,
					-0.4727051271979,-0.0686595596894,0.0536905543417,0.1493354736841,
					0.0752486133084,-1.2445400818602,-0.0091542110928,0.1144647972612,
					-0.1694089098794,-0.6843358744277,-0.0257689189138,-0.5341809772570,
					0.0515078883820,-9.8365874689499,3.3426931982170,1.0782595309598,
					-0.3188983675189,-24.5612247734375,-0.8457761654128,-1.9444116632088,
					-0.6336652164094,0.3139474205754,0.3258953246720,0.2540434853071,
					0.1819552107497,0.3001339857307,0.0397780056704,0.1020389512016,
					0.1972012262657};

				double Ebeam(double *x, const double *p) {
					double X=x[0];
					double Y=x[1];
					double dX=x[2]/10.;//*1000.0;
					double dY=x[3]/10.;//*1000.0;
					double X2=X*X; double XY=X*Y; double Y2=Y*Y;  double X3=X2*X;
					double X2Y=X2*Y; double XY2=X*Y2; double Y3=Y2*Y; double X4=X2*X2;
					double X3Y=X3*Y; double X2Y2=X2*Y2; double XY3=X*Y3; double Y4=Y2*Y2;
					double X5=X3*X2; double X4Y=X4*Y; double X3Y2=X3*Y2; double X2Y3=X2*Y3;
					double XY4=X*Y4; double Y5=Y3*Y2;
					double XnYm[21];
					XnYm[0]=1;  XnYm[1]=X; XnYm[2]=Y;
					XnYm[3]=X2; XnYm[4]=XY; XnYm[5]=Y2;
					XnYm[6]=X3; XnYm[7]=X2Y; XnYm[8]=XY2; XnYm[9]=Y3;
					XnYm[10]=X4; XnYm[11]=X3Y; XnYm[12]=X2Y2; XnYm[13]=XY3;
					XnYm[14]=Y4;
					XnYm[15]=X5; XnYm[16]=X4Y; XnYm[17]=X3Y2; XnYm[18]=X2Y3;
					XnYm[19]=XY4; XnYm[20]=Y5;
					double dX2=dX*dX; double dXdY=dX*dY; double dY2=dY*dY;
					double dX3=dX2*dX; double dX2dY=dX2*dY; double dXdY2=dX*dY2;
					double dY3=dY2*dY;  double dX4=dX2*dX2; double dX3dY=dX3*dY;
					double dX2dY2=dX2*dY2; double dXdY3=dX*dY3; double dY4=dY2*dY2;
					double dX5=dX3*dX2; double dX4dY=dX4*dY; double dX3dY2=dX3*dY2;
					double dX2dY3=dX2*dY3; double dXdY4=dX*dY4; double dY5=dY3*dY2;
					double dXndYm[21];
					dXndYm[0]=1;  dXndYm[1]=dX; dXndYm[2]=dY;
					dXndYm[3]=dX2; dXndYm[4]=dXdY; dXndYm[5]=dY2;
					dXndYm[6]=dX3; dXndYm[7]=dX2dY; dXndYm[8]=dXdY2; dXndYm[9]=dY3;
					dXndYm[10]=dX4; dXndYm[11]=dX3dY; dXndYm[12]=dX2dY2; dXndYm[13]=dXdY3;
					dXndYm[14]=dY4; dXndYm[15]=dX5; dXndYm[16]=dX4dY; dXndYm[17]=dX3dY2;
					dXndYm[18]=dX2dY3; dXndYm[19]=dXdY4; dXndYm[20]=dY5;
					double Eb=0;
					for (int i=0; i<21; i++) {
						double pp=0;
						for (int j=0; j<21; j++) {
							pp += p[i*21+j] * dXndYm[j];
						}
						Eb += pp * XnYm[i];
					}

					return Eb;
				}

			}

		}
	}
}

#endif
