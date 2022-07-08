/*
*   Filename:               hw06.c
*   Date & time:            03/12/2021
*   Author:                 Adam Hajek
*
*   Short description:      This code is a solution for school assignment PROGTEST-HW06.
*/

#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#endif /* __PROGTEST__ */

void cleanString(char *toClean) 
{
    int i = 0;

    while (toClean[i] != '\0') 
    {
        toClean[i] = toupper(toClean[i]);
        if (!isalpha(toClean[i])) 
        {
            toClean[i] = ' ';
        }
        i++;
    }
}

int sameWords(const char *a, const char *b) 
{
    int ret = 1;
    bool shouldGo = true;

    char *firstSentence = (char *) malloc(strlen(a) + 1);
    char *secondSentence = (char *) malloc(strlen(b) + 1);

    char *firstSentenceREAD = (char *) malloc(strlen(a) + 1);
    char *secondSentenceREAD = (char *) malloc(strlen(b) + 1);

    strcpy(firstSentence, a);
    strcpy(secondSentence, b);

    cleanString(firstSentence);
    cleanString(secondSentence);

    strcpy(firstSentenceREAD, firstSentence);
    strcpy(secondSentenceREAD, secondSentence);

    char *word = strtok(firstSentence, " ");

    while (word != NULL) 
    {
        if (strstr(secondSentenceREAD, word) == NULL) 
        {
            ret = 0;
            shouldGo = false;
            break;
        }

        word = strtok(NULL, " ");
    }

    if (shouldGo) 
    {
        word = strtok(secondSentence, " ");
        
        while (word != NULL) 
        {
            if (strstr(firstSentenceREAD, word) == NULL) 
            {
                ret = 0;
                break;
            }

            word = strtok(NULL, " ");
        }
    }

    free(firstSentence);
    free(secondSentence);
    free(firstSentenceREAD);
    free(secondSentenceREAD);
 
    return ret;
} 


#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  assert ( sameWords ( "He he he he he he said he he he  would do he it.", "IT said: 'He would do it.'" ) == 1 );
  assert ( sameWords ( "drahoty,><>> drahoty drahoty .", "DrAhOTy, !" ) == 1 );
  assert ( sameWords ( "Hello students.", "HELLO studEnts!" ) == 1 );
  assert ( sameWords ( " He said 'hello!'", "'Hello.' he   said." ) == 1 );
  assert ( sameWords ( "He said he would do it.", "IT said: 'He would do it.'" ) == 1 );
  assert ( sameWords ( "one two three", "one two five" ) == 0 );
  assert (sameWords("a a                               a         a a   a a   a a   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                  a a a a a           a !!!a", "a a                                                                      a a a a a           a !!!a") == 1);
  assert (sameWords(" |||||||||||||||||||||||a|||||||||||!a                                                                    !!                !! !                                             !                         !                                                                    !!                !! !                                                                   !!                !!                                           !!    a      a      !! !              a                  a              a                 a     !!        a       !!                       !!                !!", "!||||||||||||||||||||||||||a|||||||a||||||a|||||||a||||||a||a||||||||||||!A     !!!!!!!!!!!                a.!") == 1);
  assert (sameWords("a!!!!!!!!!!!!!!!!!!!!                    !!!!!!!!!!!||||||||||", "||||||||||||||||||||||||A a a a a a a a a    a                                    a!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!a!!!!!!!:?'''''''''''''''''''''''''''!!|a A a A A A A!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!") == 1);
  assert (sameWords("a a", "Aa a") == 0);
  assert (sameWords("a", "A") == 1);
  assert (sameWords("a", "") == 0);
  assert (sameWords(" ", "A") == 0);
  assert (sameWords("students.         Hello ", "HELLO studEnts!") == 1);
  assert (sameWords(" He said 'hello!'", "'Hello.' he   said.") == 1);
  assert (sameWords("one two three", "one two five") == 0);
  assert (sameWords("He said he would do it.", "IT said: 'He would do it.'") == 1);
  assert (sameWords("He said he wo"
                   "uld do it.",
                   "IT said: 'He  wo"
                   "uld do it.'") == 1);
  assert(sameWords("  \\$€\\|€ đĐłŁ#&@", "  \\$€\\|€đĐłŁ#&@") == 1);
  assert(sameWords("\na", "   \na") == 1);
  assert(sameWords(".FafhB.b VDhRShzirO'qBHXCwHuAHRSzT'.HuUlMrvJMZDIEaRjrMBDA,RnIDaOtkwpjsaZnaZBvx.WXrWWdDVDXdLF'EpwDK.BkSL'epSCUYNVuzAsENFtvvPBhSKxDeuzLJqWTJFmaZnEkifDBXuBseDOmH!.GktIkaWDfyoSqyPdCXxvTpkfEKKpQr HKGwVfaHpmCf.ZcCaXAv!A. QtAvvqDYg?GIm?YLpqNnuEcabU?NSgTCxhtx!HqoomZUEjBwtuPjFGEWkrx QNfcWYVw!MynJgEBHDKxPzWhmxLkv'bxzuVgnzvbqMpyCrj'olKEfbD.!Eqqdrtoo'j,O QKvXJambDcEGGi?gc KQlU!utq.ZtGAbvuVQGhirRpMq.. xx!JRtqO'ylrwthcgpyeX.QMamLtWypyxd!FZa,?EoDXjEREnQUkLapbbvsSb nRBGix.x'hoSGIdGra?QdnjPJZhQzbculnMcAbQVwXCovrhsNNiZZYSqIEvedIZZeRstMvyQh!LHmrBgMOFu,?xB gqn.sYjAXfWPZxdnRNOKFreaUdLHYM'gfCoVjOviMFEvo WaqP PhJNupMiuikM !D oK'zq!iOqu,mro LSyKn,?rRLWfyPLQUiBYLFEON'yXmVAx!opGJvqAtiufp'wHOcvremgdYqvUa?KUrBkDIEcRpojz.IxMatmBUUxVZUeMHnTmY' bATAcQBA.RK!JuYlVRYlHaTgs?mQ.Iym'uxHWJkOwG.z pexMkFUnEhgLzdxkheD?KsHULpbasnCsNDLQgWWtijliTAqMLcuQDLW.F.QV?ofLtP.?hzXZWuuTdA'di!xNFijkucIF,ID minMrUMj'EfzRtGCn'FhA!?Dwf WAjLUYAhdvxCvxJ?DZAnW'aVuZjKOKBM'AhF! hkucklv!htvvU,vFrGubfrhr WZWyNAIkePXdQBQZeeZOMvCmZQsotGBLdg,lMUD?llXhL.FafhB.b VDhRShzirO'qBHXCwHuAHRSzT'.HuUlMrvJMZDIEaRjrMBDA,RnIDaOtkwpjsaZnaZBvx.WXrWWdDVDXdLF'EpwDK.BkSL'epSCUYNVuzAsENFtvvPBhSKxDeuzLJqWTJFmaZnEkifDBXuBseDOmH!.GktIkaWDfyoSqyPdCXxvTpkfEKKpQr HKGwVfaHpmCf.ZcCaXAv!A. QtAvvqDYg?GIm?YLpqNnuEcabU?NSgTCxhtx!HqoomZUEjBwtuPjFGEWkrx QNfcWYVw!MynJgEBHDKxPzWhmxLkv'bxzuVgnzvbqMpyCrj'olKEfbD.!Eqqdrtoo'j,O QKvXJambDcEGGi?gc KQlU!utq.ZtGAbvuVQGhirRpMq.. xx!JRtqO'ylrwthcgpyeX.QMamLtWypyxd!FZa,?EoDXjEREnQUkLapbbvsSb nRBGix.x'hoSGIdGra?QdnjPJZhQzbculnMcAbQVwXCovrhsNNiZZYSqIEvedIZZeRstMvyQh!LHmrBgMOFu,?xB gqn.sYjAXfWPZxdnRNOKFreaUdLHYM'gfCoVjOviMFEvo WaqP PhJNupMiuikM !D oK'zq!iOqu,mro LSyKn,?rRLWfyPLQUiBYLFEON'yXmVAx!opGJvqAtiufp'wHOcvremgdYqvUa?KUrBkDIEcRpojz.IxMatmBUUxVZUeMHnTmY' bATAcQBA.RK!JuYlVRYlHaTgs?mQ.Iym'uxHWJkOwG.z pexMkFUnEhgLzdxkheD?KsHULpbasnCsNDLQgWWtijliTAqMLcuQDLW.F.QV?ofLtP.?hzXZWuuTdA'di!xNFijkucIF,ID minMrUMj'EfzRtGCn'FhA!?Dwf WAjLUYAhdvxCvxJ?DZAnW'aVuZjKOKBM'AhF! hkucklv!htvvU,vFrGubfrhr WZWyNAIkePXdQBQZeeZOMvCmZQsotGBLdg,lMUD?llXhL", ".FafhB.b VDhRShzirO'qBHXCwHuAHRSzT'.HuUlMrvJMZDIEaRjrMBDA,RnIDaOtkwpjsaZnaZBvx.WXrWWdDVDXdLF'EpwDK.BkSL'epSCUYNVuzAsENFtvvPBhSKxDeuzLJqWTJFmaZnEkifDBXuBseDOmH!.GktIkaWDfyoSqyPdCXxvTpkfEKKpQr HKGwVfaHpmCf.ZcCaXAv!A. QtAvvqDYg?GIm?YLpqNnuEcabU?NSgTCxhtx!HqoomZUEjBwtuPjFGEWkrx QNfcWYVw!MynJgEBHDKxPzWhmxLkv'bxzuVgnzvbqMpyCrj'olKEfbD.!Eqqdrtoo'j,O QKvXJambDcEGGi?gc KQlU!utq.ZtGAbvuVQGhirRpMq.. xx!JRtqO'ylrwthcgpyeX.QMamLtWypyxd!FZa,?EoDXjEREnQUkLapbbvsSb nRBGix.x'hoSGIdGra?QdnjPJZhQzbculnMcAbQVwXCovrhsNNiZZYSqIEvedIZZeRstMvyQh!LHmrBgMOFu,?xB gqn.sYjAXfWPZxdnRNOKFreaUdLHYM'gfCoVjOviMFEvo WaqP PhJNupMiuikM !D oK'zq!iOqu,mro LSyKn,?rRLWfyPLQUiBYLFEON'yXmVAx!opGJvqAtiufp'wHOcvremgdYqvUa?KUrBkDIEcRpojz.IxMatmBUUxVZUeMHnTmY' bATAcQBA.RK!JuYlVRYlHaTgs?mQ.Iym'uxHWJkOwG.z pexMkFUnEhgLzdxkheD?KsHULpbasnCsNDLQgWWtijliTAqMLcuQDLW.F.QV?ofLtP.?hzXZWuuTdA'di!xNFijkucIF,ID minMrUMj'EfzRtGCn'FhA!?Dwf WAjLUYAhdvxCvxJ?DZAnW'aVuZjKOKBM'AhF! hkucklv!htvvU,vFrGubfrhr WZWyNAIkePXdQBQZeeZOMvCmZQsotGBLdg,lMUD?llXhL") == 1);
  assert(sameWords("\nOIFMVDSKngCheexAYvASscdGn OIFMVDSKngCheexAYvASscdGn OIFMVDSKngCheexAYvASscdGn OIFMVDSKngCheexAYvASscdGn OIFMVDSKngCheexAYvASscdGn OIFMVDSKngCheexAYvASscdGn OIFMVDSKngCheexAYvASscdGn OIFMVDSKngCheexAYvASscdGn", "OIFMVDSKngCheexAYvASscdGn") == 1);
  assert(sameWords("thisisalongwordaverylongwordbutthelengthisstillsmallerthanthelengthofthelongestwordintheworld thisisalongwordaverylongwordbutthelengthisstillsmallerthanthelengthofthelongestwordintheworld", "thisisalongwordaverylongwordbutthelengthisstillsmallerthanthelengthofthelongestwordintheworld") == 1);
  assert(sameWords("is simply dummy text of the pr inting and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum. is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum. is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.", "is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum. is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.") == 1);
  
  
  return 0;
}
#endif /* __PROGTEST__ */
