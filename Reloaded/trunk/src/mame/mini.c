/******************************************************************************

    mini.c

    mamedriv.c substitute file for "mini" MAME builds.

    Copyright Nicola Salmoria and the MAME Team.
    Visit http://mamedev.org for licensing and usage restrictions.

    The list of used drivers. Drivers have to be included here to be recognized
    by the executable.

    To save some typing, we use a hack here. This file is recursively #included
    twice, with different definitions of the DRIVER() macro. The first one
    declares external references to the drivers; the second one builds an array
    storing all the drivers.

******************************************************************************/

#include "driver.h"

#ifndef DRIVER_RECURSIVE

#define DRIVER_RECURSIVE

/* step 1: declare all external references */
#define DRIVER(NAME) GAME_EXTERN(NAME);
#include "mini.c"

/* step 2: define the drivers[] array */
#undef DRIVER
#define DRIVER(NAME) &GAME_NAME(NAME),
const game_driver * const drivers[] =
{
#include "mini.c"
	0	/* end of array */
};

#else	/* DRIVER_RECURSIVE */

	/* Bally / Sente games */
	DRIVER( sentetst )
	DRIVER( cshift )	/* (c) 1984 */
	DRIVER( gghost )	/* (c) 1984 */
	DRIVER( hattrick )	/* (c) 1984 */
	DRIVER( otwalls )	/* (c) 1984 */
	DRIVER( snakepit )	/* (c) 1984 */
	DRIVER( snakjack )	/* (c) 1984 */
	DRIVER( stocker )	/* (c) 1984 */
	DRIVER( triviag1 )	/* (c) 1984 */
	DRIVER( trivia12 )	/* (c) 1984 */
	DRIVER( triviag2 )	/* (c) 1984 */
	DRIVER( triviasp )	/* (c) 1984 */
	DRIVER( triviayp )	/* (c) 1984 */
	DRIVER( triviabb )	/* (c) 1984 */
	DRIVER( triviaes )	/* (c) 1984 */
	DRIVER( gimeabrk )	/* (c) 1985 */
	DRIVER( minigolf )	/* (c) 1985 */
	DRIVER( minigolf2 )	/* (c) 1985 */
	DRIVER( toggle )	/* (c) 1985 */
	DRIVER( nametune )	/* (c) 1986 */
	DRIVER( nstocker )	/* (c) 1986 */
	DRIVER( nstocker2 )	/* (c) 1986 */
	DRIVER( sfootbal )	/* (c) 1986 */
	DRIVER( spiker )	/* (c) 1986 */
	DRIVER( stompin )	/* (c) 1986 */
	DRIVER( rescraid )	/* (c) 1987 */
	DRIVER( rescraida )	/* (c) 1987 */
	DRIVER( grudge )	/* prototype - Bally/Midway */
	DRIVER( shrike )	/* (c) 1987 */
	DRIVER( gridlee )	/* [1983 Videa] prototype - no copyright notice */

	/* Exidy games */
	DRIVER( carpolo )	/* (c) 1977 */
	DRIVER( sidetrac )	/* (c) 1979 */
	DRIVER( targ )		/* (c) 1980 */
	DRIVER( targc )		/* (c) 1980 */
	DRIVER( spectar )	/* (c) 1980 */
	DRIVER( spectar1 )	/* (c) 1980 */
	DRIVER( rallys )	/* (c) 1980 Novar (bootleg?) */
	DRIVER( phantoma )	/* (c) 1980 Jeutel (bootleg?) */
	DRIVER( venture )	/* (c) 1981 */
	DRIVER( venture2 )	/* (c) 1981 */
	DRIVER( venture4 )	/* (c) 1981 */
	DRIVER( teetert )	/* (c) 1981 */
	DRIVER( mtrap )		/* (c) 1981 */
	DRIVER( mtrap3 )	/* (c) 1981 */
	DRIVER( mtrap4 )	/* (c) 1981 */
	DRIVER( pepper2 )	/* (c) 1982 */
	DRIVER( hardhat )	/* (c) 1982 */
	DRIVER( fax )		/* (c) 1983 */
	DRIVER( fax2 )		/* (c) 1983 */
	DRIVER( circus )	/* no copyright notice [1977?] */
	DRIVER( circusse )	/* bootleg */
	DRIVER( robotbwl )	/* no copyright notice */
	DRIVER( crash )		/* Exidy [1979?] */
	DRIVER( ripcord )	/* Exidy [1977?] */
	DRIVER( starfire )	/* Exidy [1979?] */
	DRIVER( starfirea )	/* Exidy [1979?] */
	DRIVER( fireone )	/* (c) 1979 Exidy */
	DRIVER( starfir2 )	/* (c) 1979 Exidy */
	DRIVER( victory )	/* (c) 1982 */
	DRIVER( victorba )	/* (c) 1982 */
	DRIVER( topgunnr )	/* (c) 1986 */

	/* Gaelco 2D games */
	DRIVER( mastboy )	/* (c) 1987 - No Ref on the PCB */
	DRIVER( mastboyi )	/* (c) 1987 - No Ref on the PCB */
	DRIVER( xorworld )	/* (c) 1990 - prototype */
	DRIVER( bigkarnk )	/* (c) 1991 - Ref 901112-1 */
	/* Master Boy 2 */	/* (c) 1991 - Ref ??? */
	DRIVER( splash )	/* (c) 1992 - Ref 922804 */
	DRIVER( splash10 )	/* (c) 1992 - Ref 922804 */
	DRIVER( paintlad )	/* (c) 1992 - ver 1.3 */
	DRIVER( roldfrog )	/* not a gaelco game but based on splash code */
	DRIVER( roldfroga )	/* not a gaelco game but based on splash code */
	DRIVER( rebus )		/* not a gaelco game but on similar hw to splash */
	DRIVER( funystrp )	/* not a gaelco game but on similar hw to splash */
	DRIVER( puckpepl )	/* not a gaelco game but on similar hw to splash */
	DRIVER( thoop )		/* (c) 1992 - Ref 922804/1 */
	DRIVER( squash )	/* (c) 1992 - Ref 922804/2 */
	DRIVER( wrally )	/* (c) 1993 - Ref 930705 */
	DRIVER( wrallya )	/* (c) 1993 - Ref 930705 */
	DRIVER( wrallyb )	/* (c) 1993 - Ref 930217 */
	DRIVER( glass )		/* (c) 1993 - Ref 931021 */
	DRIVER( glass10 )	/* (c) 1993 - Ref 931021 */
	DRIVER( glassbrk )	/* (c) 1993 - Ref 931021 shows "Break Edition" on a real PCB */
	DRIVER( targeth )	/* (c) 1994 - Ref 940531 */
	DRIVER( targetha )	/* (c) 1994 - Ref 940531 */
	DRIVER( thoop2 )	/* (c) 1994 - Ref ??? */
	DRIVER( aligator )	/* (c) 1994 - Ref 940411 */
	DRIVER( aligatorun )	/* (c) 1994 - Ref 940411 (unprotected) */
	DRIVER( biomtoy )	/* (c) 1995 - Ref 922804/2 - (unprotected) */
	DRIVER( touchgo )	/* (c) 1995 - Ref 950906 */
	DRIVER( touchgon )	/* (c) 1995 - Ref 950906 */
	DRIVER( touchgoe )	/* (c) 1995 - Ref 950510-1 */
	DRIVER( wrally2 )	/* (c) 1995 - Ref 950510 */
	DRIVER( maniacsp )	/* (c) 1996 - Ref 922804/2 - (prototype) */
	DRIVER( maniacsq )	/* (c) 1996 - Ref ??? - (unprotected) */
	DRIVER( snowboar )	/* (c) 1996 - Ref 960419/1 */
	DRIVER( snowboara )	/* (c) 1996 - Ref 960419/1 */
	DRIVER( bang )		/* (c) 1998 - Ref ??? */
	DRIVER( bangj )		/* (c) 1999 - Ref ??? */
	DRIVER( grtesoro )	/* (c) 1999 - Ref ??? */

	/* "Pacman hardware" games */
	DRIVER( puckman )	/* (c) 1980 Namco */
	DRIVER( puckmana )	/* (c) 1980 Namco */
	DRIVER( puckmanf )	/* hack */
	DRIVER( puckmanh )	/* hack */
	DRIVER( pacman )	/* (c) 1980 Midway */
	DRIVER( pacmanf )	/* hack */
	DRIVER( puckmod )	/* (c) 1981 Namco */
	DRIVER( pacmod )	/* (c) 1981 Midway */
	DRIVER( newpuc2 )	/* hack */
	DRIVER( newpuc2b )	/* hack */
	DRIVER( newpuckx )	/* hack */
	DRIVER( pacheart )	/* hack */
	DRIVER( hangly )	/* hack */
	DRIVER( hangly2 )	/* hack */
	DRIVER( hangly3 )	/* hack */
	DRIVER( piranhah )	/* hack */
	DRIVER( abscam )	/* hack */
	DRIVER( crush )		/* (c) 1981 Kural Samno Electric Ltd */
	DRIVER( crushbl )	/* bootleg */
	DRIVER( crushbl2 )	/* bootleg 2*/
	DRIVER( crush2 )	/* (c) 1981 Kural Esco Electric Ltd - bootleg? */
	DRIVER( crush3 )	/* Kural Electric Ltd - bootleg? */
	DRIVER( crush4 )	/* Kural TWT */
	DRIVER( maketrax )	/* (c) 1981 Williams, high score table says KRL (fur Kural) */
	DRIVER( maketrxb )	/* (c) 1981 [Kural] (Williams license) */
	DRIVER( korosuke )	/* (c) 1981 Kural Electric */
	DRIVER( mbrush )	/* 1981 bootleg */
	DRIVER( paintrlr )	/* 1981 bootleg */
	DRIVER( crushs )	/* 1981 bootleg */
	DRIVER( pacplus )	/* (c) 1982 Namco (Midway license) */
	DRIVER( joyman )	/* hack */
	DRIVER( ctrpllrp )	/* hack */
	DRIVER( eyes )		/* (c) 1982 Digitrex Techstar + "Rockola presents" */
	DRIVER( eyes2 )		/* (c) 1982 Techstar + "Rockola presents" */
	DRIVER( eyeszac )	/* (c) 1982 Zaccaria / bootleg */
	DRIVER( mrtnt )		/* (c) 1983 Telko */
	DRIVER( gorkans )	/* (c) 1984 Techstar */
	DRIVER( eggor )		/* (c) 1983 Telko */
	DRIVER( jumpshot )	/* (c) 1985 Bally Midway */
	DRIVER( jumpshtp )	/* (c) 1985 Bally Midway */
	DRIVER( shootbul )	/* (c) 1985 Bally Midway */
	DRIVER( piranha )	/* GL */
	DRIVER( piranhao )	/* GL */
	DRIVER( nmouse )	/* (c) 1981 Amenip (Palcom Queen River) */
	DRIVER( nmouseb )	/* (c) 1981 Amenip Nova Games Ltd. */
	DRIVER( mspacman )	/* (c) 1981 Midway */ /* made by General Computer */
	DRIVER( mspacmnf )	/* hack */
	DRIVER( mspacmat )	/* hack */
	DRIVER( woodpeck )	/* (c) 1981 Amenip (Palcom Queen River) */
	DRIVER( woodpeca )	/* (c) 1981 Amenip Nova Games Ltd. */
	DRIVER( mspacmab )	/* bootleg */
	DRIVER( mspacmbe )	/* bootleg */
	DRIVER( pacgal )	/* hack */
	DRIVER( mspacpls )	/* hack */
	DRIVER( ponpoko )	/* (c) 1982 Sigma Ent. Inc. */
	DRIVER( ponpokov )	/* (c) 1982 Sigma Ent. Inc. + Venture Line license */
	DRIVER( lizwiz )	/* (c) 1985 Techstar + "Sunn presents" */
	DRIVER( alibaba )	/* (c) 1982 Sega */
	DRIVER( dremshpr )	/* (c) 1982 Sanritsu */
	DRIVER( vanvan )	/* (c) 1983 Sanritsu */
	DRIVER( vanvank )	/* (c) 1983 Karateco (bootleg?) */
	DRIVER( vanvanb )	/* (c) 1983 Karateco (bootleg?) */
	DRIVER( bwcasino )	/* (c) 1983 Epos Coropration */
	DRIVER( acitya )	/* (c) 1983 Epos Corporation */
	DRIVER( theglobp )	/* (c) 1983 Epos Corporation */
	DRIVER( sprglobp )	/* (c) 1983 Epos Corporation */
	DRIVER( sprglbpg )	/* German bootleg */
	DRIVER( beastf )	/* (c) 1984 Epos Corporation */
	DRIVER( rocktrv2 )	/* (c) 1986 Triumph Software Inc */
	DRIVER( bigbucks )	/* (c) 1986 Dynasoft Inc. */
	DRIVER( mschamp )	/* hack */
	DRIVER( cannonbp )	/* hack */

	/* S2650 Pacman Kits */
	DRIVER( drivfrcp )	/* (c) 1984 Shinkai Inc. (Magic Eletronics Inc. licence) */
	DRIVER( 8bpm )		/* (c) 1985 Seatongrove Ltd (Magic Eletronics USA licence) */
	DRIVER( porky )		/* (c) 1985 Shinkai Inc. (Magic Eletronics Inc. licence) */

	DRIVER( pengo )		/* 834-0386 (c) 1982 Sega */
	DRIVER( pengo2 )	/* 834-0386 (c) 1982 Sega */
	DRIVER( pengo2u )	/* 834-0386 (c) 1982 Sega */
	DRIVER( pengo3u )	/* 834-0386 (c) 1982 Sega */
	DRIVER( pengo4 )	/* 834-0386 (c) 1982 Sega */
	DRIVER( pengob )	/* bootleg */
	DRIVER( penta )		/* bootleg */
	DRIVER( jrpacmbl )	/* bootleg on Pengo HW */

	DRIVER( jrpacman )	/* (c) 1983 Midway */

	/* Epos games */
	DRIVER( megadon )	/* (c) 1982 */
	DRIVER( catapult )	/* (c) 1982 */
	DRIVER( suprglob )	/* (c) 1983 */
	DRIVER( theglob )	/* (c) 1983 */
	DRIVER( theglob2 )	/* (c) 1983 */
	DRIVER( theglob3 )	/* (c) 1983 */
	DRIVER( igmo )		/* (c) 1984 */
	DRIVER( dealer )	/* (c) 198? */
	DRIVER( revenger )	/* (c) 1984 */

	/* "Galaxian hardware" games */
	DRIVER( galaxian )	/* (c) Namco */
	DRIVER( galaxiana )	/* (c) Namco */
	DRIVER( galaxianm )	/* (c) Midway */
	DRIVER( galaxianmo )/* (c) Midway */
	DRIVER( galaxiant )	/* (c) Taito */
	DRIVER( superg )	/* hack */
	DRIVER( galapx )	/* hack */
	DRIVER( moonaln )	/* [Nichibutsu] (Karateco license) or hack */
	DRIVER( galap1 )	/* hack */
	DRIVER( galap4 )	/* hack */
	DRIVER( galturbo )	/* hack */
	DRIVER( swarm )		/* hack */
	DRIVER( zerotime )	/* hack */
	DRIVER( starfght )	/* hack */
	DRIVER( galaxbsf )	/* hack */
	DRIVER( kamakazi3 )	/* Video Games (UK) Ltd., hack or bootleg? */
	DRIVER( tst_galx )	/* Galaxian Test ROM */
	DRIVER( gmgalax )	/* bootleg */
	DRIVER( pisces )	/* Subelectro */
	DRIVER( piscesb )	/* bootleg */
	DRIVER( omni )		/* bootleg */
	DRIVER( uniwars )	/* (c) Irem */
	DRIVER( gteikoku )	/* (c) Irem */
	DRIVER( gteikokb )	/* bootleg */
	DRIVER( gteikob2 )	/* bootleg */
	DRIVER( spacbatt )	/* bootleg */
	DRIVER( spacbat2 )	/* bootleg */
	DRIVER( spacempr )	/* bootleg */
	DRIVER( skyraidr )	/* bootleg */
	DRIVER( batman2 )	/* bootleg */
	DRIVER( warofbug )	/* (c) 1981 Armenia */
	DRIVER( redufo )	/* bootleg - original should be (c) Artic / Arcade TV Game List (P.104, Left, 25 from top) */
	DRIVER( exodus )	/* Subelectro - bootleg? */
	DRIVER( streakng )	/* [1980] Shoei */
	DRIVER( pacmanbl )	/* bootleg */
	DRIVER( pacmanbla )	/* bootleg */
	DRIVER( phoenxp2 )	/* bootleg */
	DRIVER( atlantisb )	/* bootleg */
	DRIVER( tenspot )	/* (c) 1982 Thomas Automatics */
	DRIVER( devilfsg )	/* (c) 1984 Vision / Artic (bootleg?) */
	DRIVER( zigzag )	/* (c) 1982 LAX */
	DRIVER( zigzag2 )	/* (c) 1982 LAX */
	DRIVER( jumpbug )	/* (c) 1981 Rock-ola */
	DRIVER( jumpbugb )	/* (c) 1981 Sega */
	DRIVER( levers )	/* (c) 1983 Rock-ola */
	DRIVER( azurian )	/* (c) 1982 Rait Electronics Ltd */
	DRIVER( orbitron )	/* (c) 1982 Signatron USA (Arcade Tv Game List - P.160, Left, 22 from top) */
	DRIVER( mooncrgx )	/* bootleg */
	DRIVER( mooncrst )	/* (c) 1980 Nichibutsu */
	DRIVER( mooncrstu )	/* (c) 1980 Nichibutsu USA */
	DRIVER( mooncrsto )	/* (c) 1980 Nichibutsu */
	DRIVER( mooncrstg )	/* (c) 1980 Gremlin */
	DRIVER( smooncrs )	/* Gremlin */
	DRIVER( mooncmw )	/* bootleg */
	DRIVER( mooncrsb )	/* bootleg */
	DRIVER( mooncrs2 )	/* bootleg */
	DRIVER( spcdrag )	/* bootleg */
	DRIVER( spcdraga )	/* bootleg */
	DRIVER( mooncrs3 )	/* bootleg */
	DRIVER( fantazia )	/* bootleg */
	DRIVER( moonqsr )	/* (c) 1980 Nichibutsu */
	DRIVER( mshuttle )	/* (c) 1981 Nichibutsu */
	DRIVER( mshuttlej )	/* (c) 1981 Nichibutsu */
	DRIVER( mshuttlej2 )/* (c) 1981 Nichibutsu */
	DRIVER( moonal2 )	/* [1980] Nichibutsu */
	DRIVER( moonal2b )	/* [1980] Nichibutsu */
	DRIVER( supergx )	/* [1980] Nichibutsu */
	DRIVER( eagle )		/* [1980] Centuri */
	DRIVER( eagle2 )	/* [1980] Centuri */
	DRIVER( eagle3 )	/* [1980] Centuri */
	DRIVER( spctbird )	/* (c) Fortrek */
	DRIVER( skybase )	/* (c) 1982 Omori Electric Co., Ltd. */
	DRIVER( checkman )	/* (c) 1982 Zilec-Zenitone */
	DRIVER( checkmanj )	/* (c) 1982 Jaleco (Zenitone/Zilec in ROM CM4, and the programmer names) */
	DRIVER( dingo )		/* (c) 1983 Ashby Computers and Graphics LTD. + Jaleco license */
	DRIVER( dingoe )	/* (c) 1983 Ashby Computers and Graphics LTD. + Jaleco license */
	DRIVER( blkhole )	/* TDS (Tokyo Denshi Sekkei) */
	DRIVER( kingball )	/* (c) 1980 Namco */
	DRIVER( kingballj )	/* (c) 1980 Namco */
	DRIVER( scorpionmc )/* bootleg */
	DRIVER( frogg )		/* bootleg */
	DRIVER( 4in1 )		/* (c) 1981 Armenia / Food and Fun */
	DRIVER( bagmanmc )	/* bootleg */
	DRIVER( dkongjrm )	/* bootleg */
	DRIVER( ozon1 )		/* (c) 1983 Proma */
	DRIVER( ladybugg )	/* bootleg */
	DRIVER( vpool )		/* bootleg */
	DRIVER( drivfrcg )	/* [1984] Shinkai (Magic Electronics USA license) */
	DRIVER( drivfrcb )	/* bootleg */
	DRIVER( bongo )		/* (c) 1983 Jetsoft */
	DRIVER( hunchbkg )	/* (c) 1983 Century */
	DRIVER( harem )		/* [1983] I.G.R. */
	DRIVER( tazzmang )	/* bootleg */
	DRIVER( racknrol )	/* (c) 1986 Status (Shinkia license) (Senko Kit) */
	DRIVER( hexpool )	/* (c) 1986 Shinkia (Senko Kit) */
	DRIVER( hexpoola )	/* (c) 1986 Shinkia (Senko Kit) */
	DRIVER( trvchlng )	/* [1985] Joyland (Senko license) */
	DRIVER( luctoday )	/* 1980 Sigma */
	DRIVER( chewing )	/* ?? unknown */
	DRIVER( catacomb )	/* 1982 MTM Games */
	DRIVER( ckongg )	/* 1981 bootleg */
	DRIVER( kkgalax )	/* 1981 bootleg */
	DRIVER( porter )	/* 1982 bootleg (Arcade TV Game List - P.98, Left, 15 from bottom) */
	DRIVER( tdpgal )	/* 1983 Design Labs / Thomas Automatics */

	/* Has some similarities with Moon Cresta but Board is very different */
	DRIVER( rockclim )	/* (c)1981 Taito */

	/* "Scramble hardware" (and variations) games */
	DRIVER( scramble )	/* GX387 (c) 1981 Konami */
	DRIVER( scrambles )	/* GX387 (c) 1981 Stern */
	DRIVER( scramblb )	/* bootleg */
	DRIVER( scramb2 )	/* bootleg */
	DRIVER( explorer )	/* bootleg */
	DRIVER( strfbomb )	/* bootleg */
	DRIVER( atlantis )	/* (c) 1981 Comsoft */
	DRIVER( atlantis2 )	/* (c) 1981 Comsoft */
	DRIVER( theend )	/* (c) 1980 Konami */
	DRIVER( theends )	/* (c) 1980 Stern */
	DRIVER( omega )		/* bootleg */
	DRIVER( ckongs )	/* bootleg */
	DRIVER( froggers )	/* bootleg */
	DRIVER( frogf )		/* bootleg */
	DRIVER( amidars )	/* GX337 (c) 1982 Konami */
	DRIVER( triplep )	/* (c) 1982 KKI */	/* made by Sanritsu? */
	DRIVER( knockout )	/* (c) 1982 KKK */
	DRIVER( mariner )	/* (c) 1981 Amenip */
	DRIVER( 800fath )	/* (c) 1981 Amenip + U.S. Billiards license */
	DRIVER( mars )		/* (c) 1981 Artic */
	DRIVER( devilfsh )	/* (c) 1982 Artic */
	DRIVER( newsin7 )	/* (c) 1983 ATW USA, Inc. */
	DRIVER( mrkougar )	/* (c) 1984 ATW */
	DRIVER( mrkougar2 )	/* (c) 1984 ATW */
	DRIVER( mrkougb )	/* bootleg */
	DRIVER( mrkougb2 )	/* bootleg */
	DRIVER( hotshock )	/* (c) 1982 E.G. Felaco */
	DRIVER( conquer )	/* (c) 1982 ???? */
	DRIVER( hunchbks )	/* (c) 1983 Century */
	DRIVER( hncholms )	/* (c) 1984 Century */
	DRIVER( cavelon )	/* (c) 1983 Jetsoft */
	DRIVER( sfx )		/* (c) 1983 Nichibutsu */
	DRIVER( skelagon )	/* (c) 1983 Nichibutsu USA */
	DRIVER( monsterz )	/* (c) 1982 Nihon (Arcade TV Game List - P.102, Left, 20 from top) */
	DRIVER( mimonscr )	/* (c) 1982 Universal Video Games (US Copyright Office info - http://cocatalog.loc.gov)*/
	DRIVER( mimonkey )	/* (c) 1982 bootleg */
	DRIVER( mimonsco )	/* (c) 1982 bootleg */
	DRIVER( scobra )	/* GX316 (c) 1981 Konami */
	DRIVER( scobras )	/* GX316 (c) 1981 Stern */
	DRIVER( scobrase )	/* GX316 (c) 1981 Stern */
	DRIVER( scobrab )	/* GX316 (c) 1981 Karateco (bootleg?) */
	DRIVER( suprheli )	/* bootleg */
	DRIVER( stratgyx )	/* GX306 (c) 1981 Konami */
	DRIVER( stratgys )	/* GX306 (c) 1981 Stern */
	DRIVER( strongx )	/* bootleg */
	DRIVER( armorcar )	/* (c) 1981 Stern */
	DRIVER( armorcar2 )	/* (c) 1981 Stern */
	DRIVER( moonwar )	/* (c) 1981 Stern */
	DRIVER( moonwara )	/* (c) 1981 Stern */
	DRIVER( spdcoin )	/* (c) 1984 Stern */
	DRIVER( darkplnt )	/* (c) 1982 Stern */
	DRIVER( tazmania )	/* (c) 1982 Stern */
	DRIVER( tazmani2 )	/* (c) 1982 Stern */
	DRIVER( calipso )	/* (c) 1982 Tago */
	DRIVER( anteater )	/* (c) 1982 Tago */
	DRIVER( anteatg )	/* (c) 1983 TV-Tuning (F.E.G. license) */
	DRIVER( anteatgb )	/* (c) 1983 Free Enterprise Games */
	DRIVER( rescue )	/* (c) 1982 Stern */
	DRIVER( aponow )	/* bootleg */
	DRIVER( minefld )	/* (c) 1983 Stern */
	DRIVER( losttomb )	/* (c) 1982 Stern */
	DRIVER( losttombh )	/* (c) 1982 Stern */
	DRIVER( superbon )	/* bootleg */
	DRIVER( hustler )	/* GX343 (c) 1981 Konami */
	DRIVER( billiard )	/* bootleg */
	DRIVER( hustlerb )	/* bootleg */
	DRIVER( frogger )	/* GX392 (c) 1981 Konami */
	DRIVER( froggers1 )	/* (c) 1981 Sega */
	DRIVER( froggers2 )	/* 834-0068 (c) 1981 Sega */
	DRIVER( froggermc )	/* 800-3110 (c) 1981 Sega */
	DRIVER( amidar )	/* GX337 (c) 1981 Konami */
	DRIVER( amidaru )	/* GX337 (c) 1982 Konami + Stern license */
	DRIVER( amidaro )	/* GX337 (c) 1982 Konami + Olympia license */
	DRIVER( amidarb )	/* bootleg */
	DRIVER( amigo )		/* bootleg */
	DRIVER( turtles )	/* (c) 1981 Stern */
	DRIVER( turpin )	/* (c) 1981 Sega */
	DRIVER( 600 )		/* GX353 (c) 1981 Konami */
	DRIVER( flyboy )	/* (c) 1982 Kaneko */
	DRIVER( flyboyb )	/* bootleg */
	DRIVER( fastfred )	/* 136009   (c) 1982 Atari */
	DRIVER( jumpcoas )	/* (c) 1983 Kaneko */
	DRIVER( jumpcoast )	/* (c) 1983 Taito */
	DRIVER( boggy84 )	/* bootleg, original is (c)1983 Taito/Kaneko */
	DRIVER( redrobin )	/* (c) 1986 Elettronolo */
	DRIVER( imago )		/* (c) 1984 Acom */
	DRIVER( imagoa )	/* (c) 1983 Acom */
	DRIVER( scorpion )	/* (c) 1982 Zaccaria */
	DRIVER( scorpiona )	/* (c) 1982 Zaccaria */
	DRIVER( scorpionb )	/* (c) 1982 Zaccaria */
	DRIVER( ad2083 )	/* (c) 1983 Midcoin */
	DRIVER( turpins )	/* (c) 1981 bootleg */

	/* "Crazy Climber hardware" games */
	DRIVER( cclimber )	/* (c) 1980 Nichibutsu */
	DRIVER( cclimberj )	/* (c) 1980 Nichibutsu */
	DRIVER( ccboot )	/* bootleg */
	DRIVER( ccboot2 )	/* bootleg */
	DRIVER( ckong )		/* (c) 1981 Falcon */
	DRIVER( ckonga )	/* (c) 1981 Falcon */
	DRIVER( ckong2j )	/* (c) 1981 Falcon */
	DRIVER( ckongjeu )	/* bootleg */
	DRIVER( ckongo )	/* bootleg */
	DRIVER( ckongalc )	/* bootleg */
	DRIVER( bigkong )	/* bootleg */
	DRIVER( monkeyd )	/* bootleg */
	DRIVER( rpatrol )	/* Orca, from a suspicious set */
	DRIVER( rpatrolb )	/* bootleg */
	DRIVER( silvland )	/* Falcon */
	DRIVER( yamato )	/* (c) 1983 Sega */
	DRIVER( yamato2 )	/* (c) 1983 Sega */
	DRIVER( toprollr )	/* (c) 1983 Jaleco */
	DRIVER( swimmer )	/* (c) 1982 Tehkan */
	DRIVER( swimmera )	/* (c) 1982 Tehkan */
	DRIVER( swimmerb )	/* (c) 1982 Tehkan */
	DRIVER( guzzler )	/* (c) 1983 Tehkan */
	DRIVER( cannonb )	/* (c) 1985 Soft */
	DRIVER( cannonb2 )	/* (c) 1985 TV Game Gruenberg */
	DRIVER( ckongb )	/* bootleg */

	/* Namco games (plus some intruders on similar hardware) */
	DRIVER( geebee )	/* [1978] Namco */
	DRIVER( geebeeb )	/* [1978] Namco (F.lli Bertolino license) */
	DRIVER( geebeeg )	/* [1978] Gremlin */
	DRIVER( bombbee )	/* [1979] Namco */
	DRIVER( cutieq )	/* (c) 1979 Namco */
	DRIVER( navarone )	/* (c) 1980 Namco */
	DRIVER( kaitei )	/* [1980] Namco */
	DRIVER( kaiteik )	/* [1980] K.K. Tokki (prototype?) */
	DRIVER( sos )		/* [1980] Namco */
	DRIVER( tankbatt )	/* (c) 1980 Namco */
	DRIVER( warpwarp )	/* (c) 1981 Namco */
	DRIVER( warpwarpr )	/* (c) 1981 [Namco] (Rock-ola license) */
	DRIVER( warpwarpr2 )/* (c) 1981 [Namco] (Rock-ola license) */
	DRIVER( rallyx )	/* (c) 1980 Namco */
	DRIVER( rallyxa )	/* (c) 1980 Namco */
	DRIVER( rallyxm )	/* (c) 1980 Midway */
	DRIVER( nrallyx )	/* (c) 1981 Namco */
	DRIVER( nrallyxb )	/* (c) 1981 Namco */
	DRIVER( jungler )	/* GX327 (c) 1981 Konami */
	DRIVER( junglers )	/* GX327 (c) 1981 Stern */
	DRIVER( tactcian )	/* GX335 (c) 1982 Sega */
	DRIVER( tactcian2 )	/* GX335 (c) 1981 Sega */
	DRIVER( locomotn )	/* GX359 (c) 1982 Konami + Centuri license */
	DRIVER( gutangtn )	/* GX359 (c) 1982 Konami + Sega license */
	DRIVER( cottong )	/* bootleg */
	DRIVER( locoboot )	/* bootleg */
	DRIVER( commsega )	/* (c) 1983 Sega */
	/* the following ones all have a custom I/O chip */
	DRIVER( bosco )		/* (c) 1981 */
	DRIVER( boscoo )	/* (c) 1981 */
	DRIVER( boscoo2 )	/* (c) 1981 */
	DRIVER( boscomd )	/* (c) 1981 Midway */
	DRIVER( boscomdo )	/* (c) 1981 Midway */
	DRIVER( galaga )	/* (c) 1981 */
	DRIVER( galagao )	/* (c) 1981 */
	DRIVER( galagamw )	/* (c) 1981 Midway */
	DRIVER( galagamk )	/* (c) 1981 Midway */
	DRIVER( galagamf )	/* (c) 1981 Midway / hack */
	DRIVER( gallag )	/* bootleg */
	DRIVER( gatsbee )	/* (c) 1984 Uchida / hack */
	DRIVER( digdug )	/* (c) 1982 */
	DRIVER( digdug1 )	/* (c) 1982 */
	DRIVER( digdugat )	/* 136007   (c) 1982 Atari */
	DRIVER( digdugat1 )	/* 136007   (c) 1982 Atari */
	DRIVER( dzigzag )	/* bootleg */
	DRIVER( digsid )	/* bootleg */
	DRIVER( xevious )	/* (c) 1982 */
	DRIVER( xeviousa )	/* 136018   (c) 1982 + Atari license */
	DRIVER( xeviousb )	/* 136018   (c) 1982 + Atari license */
	DRIVER( xeviousc )	/* 136018   (c) 1982 + Atari license */
	DRIVER( xevios )	/* bootleg */
	DRIVER( battles )	/* bootleg */
	DRIVER( sxevious )	/* (c) 1984 */
	DRIVER( sxeviousj )	/* (c) 1984 */
	DRIVER( superpac )	/* (c) 1982 */
	DRIVER( superpacm )	/* (c) 1982 Midway */
	DRIVER( pacnpal )	/* (c) 1983 */
	DRIVER( pacnpal2 )	/* (c) 1983 */
	DRIVER( pacnchmp )	/* (c) 1983 */
	DRIVER( phozon )	/* (c) 1983 */
	DRIVER( mappy )		/* (c) 1983 */
	DRIVER( mappyj )	/* (c) 1983 */
	DRIVER( digdug2 )	/* (c) 1985 */
	DRIVER( digdug2o )	/* (c) 1985 */
	DRIVER( todruaga )	/* (c) 1984 */
	DRIVER( todruagao )	/* (c) 1984 */
	DRIVER( motos )		/* (c) 1985 */
	DRIVER( grobda )	/* (c) 1984 */
	DRIVER( grobda2 )	/* (c) 1984 */
	DRIVER( grobda3 )	/* (c) 1984 */
	DRIVER( gaplus )	/* (c) 1984 */
	DRIVER( gaplusa )	/* (c) 1984 */
	DRIVER( gapluso )	/* (c) 1984 */
	DRIVER( galaga3 )	/* (c) 1984 */
	DRIVER( galaga3m )	/* (c) 1984 */
	DRIVER( galaga3a )	/* (c) 1984 */
	/* Libble Rabble board (first Japanese game using a 68000) */
	DRIVER( liblrabl )	/* (c) 1983 */
	DRIVER( toypop )	/* (c) 1986 */
	/* Z8000 games */
	DRIVER( polepos )	/* (c) 1982  */
	DRIVER( poleposa )	/* 136014   (c) 1982 + Atari license */
	DRIVER( polepos1 )	/* 136014   (c) 1982 Atari */
	DRIVER( topracer )	/* bootleg */
	DRIVER( topracra )	/* bootleg */
	DRIVER( topracrb )	/* bootleg */
	DRIVER( polepos2 )	/* (c) 1983 */
	DRIVER( polepos2a )	/* 136014   (c) 1983 + Atari license */
	DRIVER( polepos2b )	/* bootleg */
	/* no custom I/O in the following, HD63701 (or compatible) microcontroller instead */
	DRIVER( pacland )	/* (c) 1984 */
	DRIVER( pacland2 )	/* (c) 1984 */
	DRIVER( pacland3 )	/* (c) 1984 */
	DRIVER( paclandm )	/* (c) 1984 Midway */
	DRIVER( drgnbstr )	/* (c) 1984 */
	DRIVER( skykid )	/* (c) 1985 */
	DRIVER( skykido )	/* (c) 1985 */
	DRIVER( skykidd )	/* (c) 1985 */
	DRIVER( skykids )	/* (c) 1985 */
	DRIVER( aliensec )	/* (c) 1985 */
	DRIVER( baraduke )	/* (c) 1985 */
	DRIVER( metrocrs )	/* (c) 1985 */
	DRIVER( metrocrsa )	/* (c) 1985 */

	/* Namco System 1 games */
	DRIVER( shadowld )	/* (c) 1987 */
	DRIVER( youkaidk )	/* (c) 1987 (Japan new version) */
	DRIVER( youkaidko )	/* (c) 1987 (Japan old version) */
	DRIVER( dspirit )	/* (c) 1987 (Japan new version) */
	DRIVER( dspirito )	/* (c) 1987 (Japan old version) */
	DRIVER( dspirita )	/* (c) 1987 (Atari license) */
	DRIVER( blazer )	/* (c) 1987 (Japan) */
	DRIVER( quester )	/* (c) 1987 (Japan) */
	DRIVER( pacmania )	/* (c) 1987 */
	DRIVER( pacmaniaj )	/* (c) 1987 (Japan) */
	DRIVER( galaga88 )	/* (c) 1987 */
	DRIVER( galaga88j )	/* (c) 1987 (Japan) */
	DRIVER( ws )		/* (c) 1988 (Japan) */
	DRIVER( berabohm )	/* (c) 1988 (Japan) */
	DRIVER( berabohmo )	/* (c) 1988 (Japan) */
				/* 1988 Alice in Wonderland (English version of Marchen maze) */
	DRIVER( mmaze )		/* (c) 1988 (Japan) */
	DRIVER( bakutotu )	/* (c) 1988 (Japan) */
	DRIVER( wldcourt )	/* (c) 1988 (Japan) */
	DRIVER( splatter )	/* (c) 1988 (World) */
	DRIVER( splattero )	/* (c) 1988 (World) */
	DRIVER( splatterj )	/* (c) 1988 (Japan) */
	DRIVER( faceoff )	/* (c) 1988 (Japan) */
	DRIVER( rompers )	/* (c) 1989 (Japan) */
	DRIVER( romperso )	/* (c) 1989 (Japan) */
	DRIVER( blastoff )	/* (c) 1989 (Japan) */
	DRIVER( ws89 )		/* (c) 1989 (Japan) */
	DRIVER( dangseed )	/* (c) 1989 (Japan) */
	DRIVER( ws90 )		/* (c) 1990 (Japan) */
	DRIVER( pistoldm )	/* (c) 1990 (Japan) */
	DRIVER( boxyboy )	/* (c) 1990 (US) */
	DRIVER( soukobdx )	/* (c) 1990 (Japan) */
	DRIVER( puzlclub )	/* (c) 1990 (Japan) */
	DRIVER( tankfrce )	/* (c) 1991 (US, 2 Player) */
	DRIVER( tankfrce4 )	/* (c) 1991 (US, 4 Player) */
	DRIVER( tankfrcej )	/* (c) 1991 (Japan) */

	/* Namco System 2 games */
	DRIVER( finallap )	/* 87.12 Final Lap */
	DRIVER( finallapd )	/* 87.12 Final Lap */
	DRIVER( finallapc )	/* 87.12 Final Lap */
	DRIVER( finallapjc )/* 87.12 Final Lap */
	DRIVER( finallapjb )/* 87.12 Final Lap */
	DRIVER( assault )	/* (c) 1988 */
	DRIVER( assaultj )	/* (c) 1988 (Japan) */
	DRIVER( assaultp )	/* (c) 1988 (Japan) */
	DRIVER( metlhawk )	/* (c) 1988 */
	DRIVER( metlhawkj )	/* (c) 1988 */
	DRIVER( ordyne )	/* (c) 1988 */
	DRIVER( ordynej )	/* (c) 1988 */
	DRIVER( mirninja )	/* (c) 1988 (Japan) */
	DRIVER( phelios )	/* (c) 1988 (Japan) */
	DRIVER( dirtfoxj )	/* (c) 1989 (Japan) */
	DRIVER( fourtrax )	/* 89.11 */
	DRIVER( valkyrie )	/* (c) 1989 (Japan) */
	DRIVER( finehour )	/* (c) 1989 (Japan) */
	DRIVER( burnforc )	/* (c) 1989 (Japan) */
	DRIVER( burnforco )	/* (c) 1989 (Japan) */
	DRIVER( marvland )	/* (c) 1989 (US) */
	DRIVER( marvlandj )	/* (c) 1989 (Japan) */
	DRIVER( kyukaidk )	/* (c) 1990 (Japan) */
	DRIVER( kyukaidko )	/* (c) 1990 (Japan) */
	DRIVER( dsaber )	/* (c) 1990 */
	DRIVER( dsaberj )	/* (c) 1990 (Japan) */
	DRIVER( finalap2 )	/* 90.8  Final Lap 2 */
	DRIVER( finalap2j )	/* 90.8  Final Lap 2 (Japan) */
	DRIVER( gollygho )	/* 91.7  Golly Ghost */
	DRIVER( rthun2 )	/* (c) 1990 */
	DRIVER( rthun2j )	/* (c) 1990 (Japan) */
	DRIVER( sgunner )	/* (c) 1990 */
	DRIVER( sgunnerj )	/* (c) 1990 */
	DRIVER( sgunner2 )	/* (c) 1991 (US) */
	DRIVER( sgunner2j )	/* (c) 1991 (Japan) */
	DRIVER( cosmogng )	/* (c) 1991 (US) */
	DRIVER( cosmogngj )	/* (c) 1991 (Japan) */
	DRIVER( bubbletr )	/* (c) 1992 */
	DRIVER( finalap3 )	/* 92.9  Final Lap 3 */
	DRIVER( finalap3j )	/* 92.9  Final Lap 3 */
	DRIVER( luckywld )	/* (c) 1992 */
	DRIVER( luckywldj )	/* (c) 1992 */
	DRIVER( suzuka8h )	/* (c) 1992 (World) */
	DRIVER( suzuka8hj )	/* (c) 1992 (Japan) */
	DRIVER( sws )		/* (c) 1992 (Japan) */
	DRIVER( sws92 )		/* (c) 1992 (Japan) */
	DRIVER( sws92g )	/* (c) 1992 (Japan) */
	DRIVER( suzuk8h2 )	/* (c) 1993 (World) */
	DRIVER( sws93 )		/* (c) 1993 (Japan) */

	/* Universal games */
	DRIVER( cosmicg )	/* 7907 (c) 1979 */
	DRIVER( cosmica )	/* 7910 (c) [1979] */
	DRIVER( cosmica2 )	/* 7910 (c) 1979 */
	DRIVER( nomnlnd )	/* 8003 (c) [1980?] */
	DRIVER( nomnlndg )	/* 8003 (c) [1980?] + Gottlieb */
	DRIVER( magspot )	/* ???? (c) [1980] */
	DRIVER( magspot2 )	/* 8013 (c) [1980] */
	DRIVER( panic )		/* 8015 (c) 1980 */
	DRIVER( panic2 )	/* 8015 (c) 1980 */
	DRIVER( panic3 )	/* 8015 (c) 1980 */
	DRIVER( panich )	/* 8015 (c) 1980 */
	DRIVER( panicger )	/* 8015 (c) 1980 */
	DRIVER( devzone )	/* 8022 (c) [1980] */
	DRIVER( devzone2 )	/* 8022 (c) [1980] */
	DRIVER( cheekyms )	/* 8004 (c) [1980?] */
	DRIVER( zerohour )	/* 8011 (c) Universal */
	DRIVER( redclash )	/* (c) 1981 Tehkan */
	DRIVER( redclasha )	/* (c) 1981 Tehkan */
	DRIVER( redclashk )	/* (c) Kaneko (bootleg?) */
	DRIVER( cavenger )	/* 8106 (c) 1981 */
	DRIVER( ladybug )	/* 8110 (c) 1981 */
	DRIVER( ladybugb )	/* bootleg */
	DRIVER( ladybgb2 )	/* bootleg */
	DRIVER( snapjack )	/* ???? (c) */
	DRIVER( sraider )	/* ???? (c) 1982 Universal */
	DRIVER( dorodon )	/* Falcon */
	DRIVER( dorodon2 )	/* Falcon */
	DRIVER( mrdo )		/* 8201 (c) 1982 */
	DRIVER( mrdoy )		/* 8201 (c) 1982 */
	DRIVER( mrdot )		/* 8201 (c) 1982 + Taito license */
	DRIVER( mrdofix )	/* 8201 (c) 1982 + Taito license */
	DRIVER( mrlo )		/* bootleg */
	DRIVER( mrdu )		/* bootleg */
	DRIVER( yankeedo )	/* bootleg */
	DRIVER( docastle )	/* 8302 (c) 1983 */
	DRIVER( docastle2 )	/* 8302 (c) 1983 */
	DRIVER( docastleo )	/* 8302 (c) 1983 */
	DRIVER( douni )		/* 8302 (c) 1983 */
	DRIVER( dorunrun )	/* ???? (c) 1984 */
	DRIVER( dorunrun2 )	/* ???? (c) 1984 */
	DRIVER( dorunrunc )	/* ???? (c) 1984 */
	DRIVER( dorunrunca )/* ???? (c) 1984 */
	DRIVER( spiero )	/* ???? (c) 1987 */
	DRIVER( dowild )	/* ???? (c) 1984 */
	DRIVER( jjack )		/* ???? (c) 1984 */
	DRIVER( kickridr )	/* ???? (c) 1984 */
	DRIVER( idsoccer )	/* ???? (c) 1985 */
	DRIVER( superdq )	/* ???? (c) 1984 */
	DRIVER( superdqs )	/* ???? (c) 1984 */
	DRIVER( superdqa )	/* ???? (c) 1984 */

	/* Nintendo games */
	DRIVER( spacefev )	/* (c) 1979 Nintendo */
	DRIVER( spacefevo )	/* (c) 1979 Nintendo */
	DRIVER( spacefevo2 )/* (c) 1979 Nintendo */
	DRIVER( highsplt )	/* (c) 1979 Nintendo */
	DRIVER( highsplta )	/* (c) 1979 Nintendo */
	DRIVER( highspltb )	/* (c) 1979 Nintendo */
	DRIVER( spacelnc )	/* (c) 1979 Nintendo */
	DRIVER( sheriff )	/* (c) 1979 Nintendo */
	DRIVER( bandido )	/* (c) 1980 Exidy */
	DRIVER( helifire )	/* (c) 1980 Nintendo */
	DRIVER( helifirea )	/* (c) 1980 Nintendo */
	DRIVER( radarscp )	/* (c) 1980 Nintendo */
	DRIVER( radarscp1 )	/* (c) 1980 Nintendo */
	DRIVER( dkong )		/* (c) 1981 Nintendo of America */
	DRIVER( dkongo )	/* (c) 1981 Nintendo */
	DRIVER( dkongj )	/* (c) 1981 Nintendo */
	DRIVER( dkongjo )	/* (c) 1981 Nintendo */
	DRIVER( dkongjo1 )	/* (c) 1981 Nintendo */
	DRIVER( dkongf )	/* hack from Jeff's Romhack */
	DRIVER( dkongjr )	/* (c) 1982 Nintendo of America */
	DRIVER( dkongjrj )	/* (c) 1982 Nintendo */
	DRIVER( dkongjnrj )	/* (c) 1982 Nintendo */
	DRIVER( dkongjrb )	/* bootleg */
	DRIVER( jrking )	/* bootleg */
	DRIVER( dkongjre )	/* (c) 1982 Nintendo of America */
	DRIVER( dkong3 )	/* (c) 1983 Nintendo of America */
	DRIVER( dkong3j )	/* (c) 1983 Nintendo */
	DRIVER( dkong3b )	/* bootleg */
	DRIVER( mario )		/* (c) 1983 Nintendo of America */
	DRIVER( marioe )	/* (c) 1983 Nintendo of America */
	DRIVER( marioo )	/* (c) 1983 Nintendo of America */
	DRIVER( marioj )	/* (c) 1983 Nintendo */
	DRIVER( masao )		/* bootleg */
	DRIVER( pestplce )	/* bootleg on donkey kong hw */
	DRIVER( spclforc )	/* (c) 1985 Senko Industries (Magic Eletronics Inc. licence) */
	DRIVER( spcfrcii )	/* (c) 1985 Senko Industries (Magic Eletronics Inc. licence) */
	DRIVER( 8ballact )	/* (c) 1984 Seatongrove Ltd (Magic Eletronics USA licence) */
	DRIVER( 8ballact2 )	/* (c) 1984 Seatongrove Ltd (Magic Eletronics USA licence) */
	DRIVER( shootgal )	/* (c) 1984 Seatongrove Ltd (Zaccaria licence) */
	DRIVER( drakton )	/* (c) 1984 Epos Corporation */
	DRIVER( drktnjr )	/* (c) 1984 Epos Corporation */
	DRIVER( strtheat )	/* (c) 1985 Epos Corporation */
	DRIVER( hunchbkd )	/* (c) 1983 Century */
	DRIVER( sbdk )		/* (c) 1984 Century */
	DRIVER( herbiedk )	/* (c) 1984 CVS */
	DRIVER( herodk )	/* (c) 1984 Seatongrove + Crown license */
	DRIVER( herodku )	/* (c) 1984 Seatongrove + Crown license */
	DRIVER( skyskipr )	/* (c) 1981 */
	DRIVER( popeye )	/* (c) 1982 */
	DRIVER( popeyeu )	/* (c) 1982 */
	DRIVER( popeyef )	/* (c) 1982 */
	DRIVER( popeyebl )	/* bootleg */
	DRIVER( punchout )	/* (c) 1984 */
	DRIVER( punchita )	/* bootleg */
	DRIVER( spnchout )	/* (c) 1984 */
	DRIVER( spnchoutj )	/* (c) 1984 (Japan) */
	DRIVER( armwrest )	/* (c) 1985 */

	/* Nintendo Playchoice 10 games */
	DRIVER( playch10 )
	DRIVER( pc_tenis )	/* (c) 1983 Nintendo */
	DRIVER( pc_mario )	/* (c) 1983 Nintendo */
	DRIVER( pc_bball )	/* (c) 1984 Nintendo of America */
	DRIVER( pc_bfght )	/* (c) 1984 Nintendo */
	DRIVER( pc_ebike )	/* (c) 1984 Nintendo */
	DRIVER( pc_golf )	/* (c) 1984 Nintendo */
	DRIVER( pc_kngfu )	/* (c) 1984 Irem (Nintendo license) */
	DRIVER( pc_1942 )	/* (c) 1985 Capcom */
	DRIVER( pc_smb )	/* (c) 1985 Nintendo */
	DRIVER( pc_vball )	/* (c) 1986 Nintendo */
	DRIVER( pc_duckh )	/* (c) 1984 Nintendo */
	DRIVER( pc_hgaly )	/* (c) 1984 Nintendo */
	DRIVER( pc_wgnmn )	/* (c) 1984 Nintendo */
	DRIVER( pc_grdus )	/* (c) 1986 Konami */
	DRIVER( pc_grdue )	/* (c) 1986 Konami */
	DRIVER( pc_tkfld )	/* (c) 1987 Konami (Nintendo of America license) */
	DRIVER( pc_pwrst )	/* (c) 1986 Nintendo */
	DRIVER( pc_trjan )	/* (c) 1986 Capcom USA (Nintendo of America license) */
	DRIVER( pc_cvnia )	/* (c) 1987 Konami (Nintendo of America license) */
	DRIVER( pc_dbldr )	/* (c) 1987 Konami (Nintendo of America license) */
	DRIVER( pc_rnatk )	/* (c) 1987 Konami (Nintendo of America license) */
	DRIVER( pc_rygar )	/* (c) 1987 Tecmo (Nintendo of America license) */
	DRIVER( pc_cntra )	/* (c) 1988 Konami (Nintendo of America license) */
	DRIVER( pc_goons )	/* (c) 1986 Konami */
	DRIVER( pc_mtoid )	/* (c) 1986 Nintendo */
	DRIVER( pc_radrc )	/* (c) 1987 Square */
	DRIVER( pc_miket )	/* (c) 1987 Nintendo */
	DRIVER( pc_rcpam )	/* (c) 1987 Rare */
	DRIVER( pc_ngaid )	/* (c) 1989 Tecmo (Nintendo of America license) */
	DRIVER( pc_tmnt )	/* (c) 1989 Konami (Nintendo of America license) */
	DRIVER( pc_ftqst )	/* (c) 1989 Sunsoft (Nintendo of America license) */
	DRIVER( pc_bstar )	/* (c) 1989 SNK (Nintendo of America license) */
	DRIVER( pc_tbowl )	/* (c) 1989 Tecmo (Nintendo of America license) */
	DRIVER( pc_drmro )	/* (c) 1990 Nintendo */
	DRIVER( pc_ynoid )	/* (c) 1990 Capcom USA (Nintendo of America license) */
	DRIVER( pc_rrngr )	/* (c) Capcom USA (Nintendo of America license) */
	DRIVER( pc_ddrgn )	/* (c) 1988 Technos */
	DRIVER( pc_gntlt )	/* (c) 1985 Atari/Tengen (Nintendo of America license) */
	DRIVER( pc_smb2 )	/* (c) 1988 Nintendo */
	DRIVER( pc_smb3 )	/* (c) 1988 Nintendo */
	DRIVER( pc_mman3 )	/* (c) 1990 Capcom USA (Nintendo of America license) */
	DRIVER( pc_radr2 )	/* (c) 1990 Square (Nintendo of America license) */
	DRIVER( pc_suprc )	/* (c) 1990 Konami (Nintendo of America license) */
	DRIVER( pc_tmnt2 )	/* (c) 1990 Konami (Nintendo of America license) */
	DRIVER( pc_wcup )	/* (c) 1990 Technos (Nintendo license) */
	DRIVER( pc_ngai2 )	/* (c) 1990 Tecmo (Nintendo of America license) */
	DRIVER( pc_ngai3 )	/* (c) 1991 Tecmo (Nintendo of America license) */
	DRIVER( pc_pwbld )	/* (c) 1991 Taito (Nintendo of America license) */
	DRIVER( pc_rkats )	/* (c) 1991 Atlus (Nintendo of America license) */
	DRIVER( pc_pinbt )	/* (c) 1988 Rare (Nintendo of America license) */
	DRIVER( pc_cshwk )	/* (c) 1989 Rare (Nintendo of America license) */
	DRIVER( pc_sjetm )	/* (c) 1990 Rare */
	DRIVER( pc_moglf )	/* (c) 1991 Nintendo */

	/* Nintendo VS games */
	DRIVER( btlecity )	/* (c) 1985 Namco */
	DRIVER( starlstr )	/* (c) 1985 Namco */
	DRIVER( cstlevna )	/* (c) 1987 Konami */
	DRIVER( cluclu )	/* (c) 1984 Nintendo */
	DRIVER( drmario )	/* (c) 1990 Nintendo */
	DRIVER( duckhunt )	/* (c) 1985 Nintendo */
	DRIVER( excitebk )	/* (c) 1984 Nintendo */
	DRIVER( excitebkj )	/* (c) 1984 Nintendo */
	DRIVER( goonies )	/* (c) 1986 Konami */
	DRIVER( hogalley )	/* (c) 1985 Nintendo */
	DRIVER( iceclimb )	/* (c) 1984 Nintendo */
	DRIVER( iceclimbj )	/* (c) 1984 Nintendo */
	DRIVER( ladygolf )	/* (c) 1984 Nintendo */
	DRIVER( machridr )	/* (c) 1985 Nintendo */
	DRIVER( machridrj )	/* (c) 1985 Nintendo */
	DRIVER( rbibb )		/* (c) 1987 Namco */
	DRIVER( rbibba )	/* (c) 1987 Namco */
	DRIVER( suprmrio )	/* (c) 1986 Nintendo */
	DRIVER( suprmrioa )	/* (c) 1986 Nintendo */
	DRIVER( skatekds )	/* (c) 1988 (hack) */
	DRIVER( vsskykid )	/* (c) 1986 Namco */
	DRIVER( tkoboxng )	/* (c) 1987 Data East */
	DRIVER( smgolf )	/* (c) 1984 Nintendo */
	DRIVER( smgolfj )	/* (c) 1984 Nintendo */
	DRIVER( vspinbal )	/* (c) 1984 Nintendo */
	DRIVER( vspinbalj )	/* (c) 1984 Nintendo */
	DRIVER( vsslalom )	/* (c) 1986 Nintendo */
	DRIVER( vssoccer )	/* (c) 1985 Nintendo */
	DRIVER( vssoccerj )	/* (c) 1985 Nintendo */
	DRIVER( vsgradus )	/* (c) 1986 Konami */
	DRIVER( platoon )	/* (c) 1987 Ocean */
	DRIVER( vstetris )	/* (c) 1988 Atari */
	DRIVER( mightybj )	/* (c) 1986 Tecmo */
	DRIVER( jajamaru )	/* (c) 1985 Jaleco */
	DRIVER( topgun )	/* (c) 1987 Konami */
	DRIVER( bnglngby )	/* (c) 1985 Nintendo / Broderbund Software Inc. */
	DRIVER( vstennis )	/* (c) 1984 Nintendo */
	DRIVER( vstennisj )	/* (c) 1984 Nintendo */
	DRIVER( wrecking )	/* (c) 1984 Nintendo */
	DRIVER( balonfgt )	/* (c) 1984 Nintendo */
	DRIVER( vsmahjng )	/* (c) 1984 Nintendo */
	DRIVER( vsbball )	/* (c) 1984 Nintendo */
	DRIVER( vsbballj )	/* (c) 1984 Nintendo */
	DRIVER( vsbballja )	/* (c) 1984 Nintendo */
	DRIVER( vsbballjb )	/* (c) 1984 Nintendo */
	DRIVER( iceclmrj )	/* (c) 1984 Nintendo */
	DRIVER( vsgshoe )	/* (c) 1986 Nintendo */
	DRIVER( supxevs )	/* (c) 1986 Nintendo */
	DRIVER( vsfdf )		/* (c) 1986 Sunsoft */
	DRIVER( smgolfb )	/* (c) 1985 Nintendo */

	/* NES-based hacks */
	DRIVER( multigam )	/* 1992 */
	DRIVER( multigmb )	/* 1992 */
	DRIVER( multigm2 )	/* 1992 */
	DRIVER( multigm3 )	/* 19?? */
	DRIVER( cham24 )	/* 2002 */

	/* "Phoenix hardware" (and variations) games */
	DRIVER( safarir )	/* Shin Nihon Kikaku (SNK) */
	DRIVER( phoenix )	/* (c) 1980 Amstar */
	DRIVER( phoenixa )	/* (c) 1980 Amstar + Centuri license */
	DRIVER( phoenixb )	/* (c) 1980 Amstar + Centuri license */
	DRIVER( phoenixt )	/* (c) 1980 Taito */
	DRIVER( phoenixj )	/* (c) 1980 Taito */
	DRIVER( phoenix3 )	/* bootleg */
	DRIVER( phoenixc )	/* bootleg */
	DRIVER( condor )	/* bootleg */
	DRIVER( fenix )		/* bootleg */
	DRIVER( falcon )	/* bootleg */
	DRIVER( vautour )	/* bootleg (Jeutel) */
	DRIVER( falconz )	/* bootleg */
	DRIVER( vautourz )	/* bootleg */
	DRIVER( griffon )	/* bootleg (Videotron) */
	DRIVER( nextfase )	/* bootleg */
	DRIVER( pleiads )	/* (c) 1981 Tehkan */
	DRIVER( pleiadbl )	/* bootleg */
	DRIVER( pleiadce )	/* (c) 1981 Centuri + Tehkan */
	DRIVER( capitol )	/* bootleg? */
	DRIVER( survival )	/* (c) 1982 Rock-ola */
	DRIVER( naughtyb )	/* (c) 1982 Jaleco */
	DRIVER( naughtyba )	/* bootleg */
	DRIVER( naughtybc )	/* (c) 1982 Jaleco + Cinematronics */
	DRIVER( popflame )	/* (c) 1982 Jaleco */
	DRIVER( popflamea )	/* (c) 1982 Jaleco */
	DRIVER( popflameb )	/* (c) 1982 Jaleco */
	DRIVER( popflamen )	/* (c) 1982 Jaleco */
	DRIVER( trvmstr )	/* (c) 1985 Enerdyne Technologies Inc. */
	DRIVER( trvmstra )	/* (c) 1985 Enerdyne Technologies Inc. */
	DRIVER( trvmstrb )	/* (c) 1985 Enerdyne Technologies Inc. */
	DRIVER( trvmstrc )	/* (c) 1985 Enerdyne Technologies Inc. */
	DRIVER( trvgns )	/* bootleg */

	/* Technos games */
	DRIVER( scregg )	/* TA-0001 (c) 1983 */
	DRIVER( eggs )		/* TA-0002 (c) 1983 Universal USA */
	DRIVER( dommy )		/* TA-00?? (c) 1983 (Arcade TV Game List - P.90, Left, 13 from top) */
	DRIVER( bigprowr )	/* TA-0007 (c) 1983 */
	DRIVER( tagteam )	/* TA-0007 (c) 1983 + Data East license */
	DRIVER( ssozumo )	/* TA-0008 (c) 1984 */
	DRIVER( mystston )	/* TA-0010 (c) 1984 */
	DRIVER( myststono )	/* TA-0010 (c) 1984 */
	DRIVER( dogfgt )	/* TA-0011 (c) 1984 */
	DRIVER( dogfgtj )	/* TA-0011 (c) 1984 */
	DRIVER( bogeyman )	/* -0204-0 (Data East part number) (c) 1985 (Arcade TV Game List - P.96, Right, 8 from top) */
	DRIVER( matmania )	/* TA-0015 (c) 1985 + Taito America license */
	DRIVER( excthour )	/* TA-0015 (c) 1985 + Taito license */
	DRIVER( maniach )	/* TA-0017 (c) 1986 + Taito America license */
	DRIVER( maniach2 )	/* TA-0017 (c) 1986 + Taito America license */
	DRIVER( renegade )	/* TA-0018 (c) 1986 + Taito America license */
	DRIVER( kuniokun )	/* TA-0018 (c) 1986 */
	DRIVER( kuniokunb )	/* bootleg */
	DRIVER( xsleena )	/* TA-0019 (c) 1986 */
	DRIVER( xsleenab )	/* bootleg */
	DRIVER( solarwar )	/* TA-0019 (c) 1986 Taito + Memetron license */
	DRIVER( battlane )	/* -0215, -0216 (Data East part number) (c) 1986 + Taito license */
	DRIVER( battlane2 )	/* -0215, -0216 (Data East part number) (c) 1986 + Taito license */
	DRIVER( battlane3 )	/* -0215, -0216 (Data East part number) (c) 1986 + Taito license */
	DRIVER( ddragon )	/* TA-0021 (c) 1987 */
	DRIVER( ddragonu )	/* TA-0021 (c) 1987 Taito America */
	DRIVER( ddragonua )	/* TA-0021 (c) 1987 Taito America */
	DRIVER( ddragonw )	/* TA-0021 (c) 1987 Taito */
	DRIVER( ddragonw1 )	/* TA-0021 (c) 1987 Taito */
	DRIVER( ddragonb )	/* bootleg */
	DRIVER( ddragonba )	/* bootleg */
	DRIVER( ddragon6809 )	/* bootleg */
	DRIVER( ddragon6809a )	/* bootleg */
	DRIVER( ddragonb2 )	/* bootleg */
	DRIVER( spdodgeb )	/* TA-0022 (c) 1987 */
	DRIVER( nkdodge )	/* TA-0022 (c) 1987 (Japan) */
	DRIVER( nkdodgeb )	/* TA-0022 (c) 1987 (Japan) */
	DRIVER( chinagat )	/* TA-0023 (c) 1988 Taito + Romstar license (US) */
	DRIVER( saiyugou )	/* TA-0023 (c) 1988 (Japan) */
	DRIVER( saiyugoub1 )	/* bootleg */
	DRIVER( saiyugoub2 )	/* bootleg */
	DRIVER( wwfsstar )	/* TA-0024 (c) 1989 (Europe) */
	DRIVER( wwfsstara )	/* TA-0024 (c) 1989 (US, newer) */
	DRIVER( wwfsstaru )	/* TA-0024 (c) 1989 (US) */
	DRIVER( wwfsstarj )	/* TA-0024 (c) 1989 (Japan) */
	DRIVER( vball )		/* TA-0025 (c) 1988 (US) */
	DRIVER( vball2pj )	/* TA-0025 (c) 1988 (Japan) */
	DRIVER( vballb )	/* TA-0025 (c) 1988 */
	DRIVER( ddragon2 )	/* TA-0026 (c) 1988 (World) */
	DRIVER( ddragon2u )	/* TA-0026 (c) 1988 (US) */
	DRIVER( toffy )		/* (c) 1993 Midas */
	DRIVER( stoffy )	/* (c) 1994 Midas + Unico */
	DRIVER( ddungeon )	/* Game Room */
	DRIVER( ddungeone )	/* East Coast Coin Company (Melbourne) */
	DRIVER( darktowr )	/* Game Room */
	DRIVER( tstrike )	/* East Coast Coin Company (Melbourne) */
	DRIVER( tstrikea )	/* Game Room  */
	DRIVER( ctribe )	/* TA-0028 (c) 1990 (US) */
	DRIVER( ctribe1 )	/* TA-0028 (c) 1990 (US) - Set 1? */
	DRIVER( ctribej )	/* TA-0028 (c) 1990 (Japan) */
	DRIVER( ctribeb )	/* bootleg */
	DRIVER( ctribeb2 )	/* bootleg */
	DRIVER( blockout )	/* TA-0029 (c) 1989 + California Dreams */
	DRIVER( blockout2 )	/* TA-0029 (c) 1989 + California Dreams */
	DRIVER( blockoutj )	/* TA-0029 (c) 1989 + California Dreams (Japan) */
	DRIVER( agress )	/* TA-0029 (c) 1991 Palco */
	DRIVER( agressb )	/* TA-0029 (c) 1991 Palco */
	DRIVER( ddragon3 )	/* TA-0030 (c) 1990 */
	DRIVER( ddragon3p )	/* TA-0030 (c) 1990 */
	DRIVER( ddragon3j )	/* TA-0030 (c) 1990 (Japan) */
	DRIVER( ddragon3b )	/* bootleg */
	DRIVER( wwfwfest )	/* TA-0031 (c) 1991 (US) */
	DRIVER( wwfwfesta )	/* TA-0031 (c) 1991 + Tecmo license (US) */
	DRIVER( wwfwfestb )	/* bootleg */
	DRIVER( wwfwfestj )	/* TA-0031 (c) 1991 (Japan) */
	DRIVER( shadfrce )	/* TA-0032 (c) 1993 (US) */
	DRIVER( shadfrcej )	/* TA-0032 (c) 1993 (Japan) */
	DRIVER( shadfrcejv2 )/* TA-0032 (c) 1993 (Japan) */

	/* Tehkan / Tecmo games (Tehkan became Tecmo in 1986) */
	DRIVER( senjyo )	/* (c) 1983 Tehkan */
	DRIVER( starforc )	/* (c) 1984 Tehkan */
	DRIVER( starforce )	/* (c) 1984 Tehkan */
	DRIVER( starforcb )	/* (c) 1984 Tehkan */
	DRIVER( starforca )	/* (c) 1984 Tehkan */
	DRIVER( megaforc )	/* (c) 1985 Tehkan + Video Ware license */
	DRIVER( baluba )	/* (c) 1986 Able Corp. */
	DRIVER( bombjack )	/* (c) 1984 Tehkan */
	DRIVER( bombjack2 )	/* (c) 1984 Tehkan */
	DRIVER( pbaction )	/* (c) 1985 Tehkan */
	DRIVER( pbaction2 )	/* (c) 1985 Tehkan */
	DRIVER( pbaction3 )	/* (c) 1985 Tehkan */
	DRIVER( pbaction4 )	/* (c) 1985 Tehkan */
						/* 6009 Tank Busters */
	DRIVER( ponttehk )	/* 6011 - (c) 1985 Tehkan */
	DRIVER( lvpoker )	/* ???? - (c) 1985 Tehkan */
	DRIVER( lvcards )	/* (c) 1985 Tehkan */
	DRIVER( tehkanwc )	/* (c) 1985 Tehkan */
	DRIVER( tehkanwcb )	/* bootleg */
	DRIVER( tehkanwcc )	/* bootleg */
	DRIVER( gridiron )	/* (c) 1985 Tehkan */
	DRIVER( teedoff )	/* 6102 - (c) 1986 Tecmo */
	DRIVER( solomon )	/* (c) 1986 Tecmo */
	DRIVER( solomonj )	/* (c) 1986 Tecmo */
	DRIVER( rygar )		/* 6002 - (c) 1986 Tecmo */
	DRIVER( rygar2 )	/* 6002 - (c) 1986 Tecmo */
	DRIVER( rygar3 )	/* 6002 - (c) 1986 Tecmo */
	DRIVER( rygarj )	/* 6002 - (c) 1986 Tecmo */
	DRIVER( gemini )	/* (c) 1987 Tecmo */
	DRIVER( silkworm )	/* 6217 - (c) 1988 Tecmo */
	DRIVER( silkworm2 )	/* 6217 - (c) 1988 Tecmo */
	DRIVER( backfirt )	/* bootleg [(c) 1988 Tecmo] */
	DRIVER( tbowl )		/* 6206 - (c) 1987 Tecmo */
	DRIVER( tbowlj )	/* 6206 - (c) 1987 Tecmo */
	DRIVER( shadoww )	/* 6215 - (c) 1988 Tecmo (World) */
	DRIVER( shadowwa )	/* 6215 - (c) 1988 Tecmo (World) */
	DRIVER( gaiden )	/* 6215 - (c) 1988 Tecmo (US) */
	DRIVER( ryukendn )	/* 6215 - (c) 1989 Tecmo (Japan) */
	DRIVER( ryukendna )	/* 6215 - (c) 1989 Tecmo (Japan) */
	DRIVER( mastninj )	/* bootleg */
	DRIVER( wildfang )	/* (c) 1989 Tecmo */
	DRIVER( tknight )	/* (c) 1989 Tecmo */
	DRIVER( stratof )	/* (c) 1991 Tecmo */
	DRIVER( raiga )		/* (c) 1991 Tecmo */
	DRIVER( drgnbowl )	/* (c) 1992 Nics */
	DRIVER( wc90 )		/* (c) 1989 Tecmo */
	DRIVER( wc90a )		/* (c) 1989 Tecmo */
	DRIVER( wc90b )		/* (c) 1989 Tecmo */
	DRIVER( wc90t )		/* (c) 1989 Tecmo */
	DRIVER( wc90b1 )	/* bootleg */
	DRIVER( wc90b2 )	/* bootleg */
	DRIVER( spbactn )	/* 9002 - (c) 1991 Tecmo */
	DRIVER( spbactnj )	/* 9002 - (c) 1991 Tecmo */
	DRIVER( fstarfrc )	/* (c) 1992 Tecmo */
	DRIVER( fstarfrcj )	/* (c) 1992 Tecmo */
	DRIVER( ginkun )	/* (c) 1995 Tecmo */
	DRIVER( deroon )	/* (c) 1996 Tecmo */
	DRIVER( tkdensho )	/* (c) 1996 Tecmo */
	DRIVER( tkdenshoa )	/* (c) 1996 Tecmo */

	/* Konami bitmap games */
	DRIVER( tutankhm )	/* GX350 (c) 1982 Konami */
	DRIVER( tutankhms )	/* GX350 (c) 1982 Stern */
	DRIVER( junofrst )	/* GX310 (c) 1983 Konami */
	DRIVER( junofrstg )	/* GX310 (c) 1983 Konami + Gottlieb license */

	/* Konami games */
	DRIVER( pooyan )	/* GX320 (c) 1982 */
	DRIVER( pooyans )	/* GX320 (c) 1982 Stern */
	DRIVER( pootan )	/* bootleg */
	DRIVER( timeplt )	/* GX393 (c) 1982 */
	DRIVER( timepltc )	/* GX393 (c) 1982 + Centuri license*/
	DRIVER( timeplta )	/* GX393 (c) 1982 + Atari license*/
	DRIVER( spaceplt )	/* bootleg */
	DRIVER( psurge )	/* (c) 1988 unknown (NOT Konami) */
	DRIVER( megazone )	/* GX319 (c) 1983 */
	DRIVER( megazonea )	/* GX319 (c) 1983 */
	DRIVER( megazoneb )	/* GX319 (c) 1983 + Kosuka */
	DRIVER( megazonec )	/* GX319 (c) 1983 + Kosuka */
	DRIVER( megazonei )	/* GX319 (c) 1983 + Interlogic / Kosuka */
	DRIVER( pandoras )	/* GX328 (c) 1984 + Interlogic */
	DRIVER( gyruss )	/* GX347 (c) 1983 */
	DRIVER( gyrussce )	/* GX347 (c) 1983 + Centuri license */
	DRIVER( venus )		/* bootleg */
	DRIVER( trackfld )	/* GX361 (c) 1983 */
	DRIVER( trackfldc )	/* GX361 (c) 1983 + Centuri license */
	DRIVER( hyprolym )	/* GX361 (c) 1983 */
	DRIVER( hyprolymb )	/* bootleg */
	DRIVER( atlantol )	/* bootleg */
	DRIVER( wizzquiz )	/* (c) 1985 Konami */
	DRIVER( wizzquiza )	/* (c) 1985 Zilec-Zenitone */
	DRIVER( reaktor )	/* (c) 1985 Zilec */
	DRIVER( mastkin )	/* (c) 1988 Du Tech */
	DRIVER( rocnrope )	/* GX364 (c) 1983 */
	DRIVER( rocnropek )	/* GX364 (c) 1983 + Kosuka */
	DRIVER( circusc )	/* GX380 (c) 1984 */
	DRIVER( circusc2 )	/* GX380 (c) 1984 */
	DRIVER( circusc3 )	/* GX380 (c) 1984 */
	DRIVER( circuscc )	/* GX380 (c) 1984 + Centuri license */
	DRIVER( circusce )	/* GX380 (c) 1984 + Centuri license */
	DRIVER( tp84 )		/* GX388 (c) 1984 */
	DRIVER( tp84a )		/* GX388 (c) 1984 */
	DRIVER( tp84b )		/* GX388 (c) 1984 */
	DRIVER( hyperspt )	/* GX330 (c) 1984 + Centuri */
	DRIVER( hpolym84 )	/* GX330 (c) 1984 */
	DRIVER( sbasketb )	/* GX405 (c) 1984 (Version I, Encrypted) */
	DRIVER( sbasketh )	/* GX405 (c) 1984 (Version H, Unprotected) */
	DRIVER( sbasketg )	/* GX405 (c) 1984 (Version G, Encrypted) */
	DRIVER( sbaskete )	/* GX405 (c) 1984 (Version E, Encrypted) */
	DRIVER( mikie )		/* GX469 (c) 1984 */
	DRIVER( mikiej )	/* GX469 (c) 1984 */
	DRIVER( mikiehs )	/* GX469 (c) 1984 */
	DRIVER( roadf )		/* GX461 (c) 1984 */
	DRIVER( roadf2 )	/* GX461 (c) 1984 */
	DRIVER( yiear )		/* GX407 (c) 1985 */
	DRIVER( yiear2 )	/* GX407 (c) 1985 */
	DRIVER( kicker )	/* GX477 (c) 1985 */
	DRIVER( shaolins )	/* GX477 (c) 1985 */
	DRIVER( pingpong )	/* GX555 (c) 1985 */
	DRIVER( merlinmm )	/* (c) 1986 Zilec-Zenitone */
	DRIVER( cashquiz )	/* (c) 1986 Zilec-Zenitone */
	DRIVER( gberet )	/* GX577 (c) 1985 */
	DRIVER( rushatck )	/* GX577 (c) 1985 */
	DRIVER( gberetb )	/* bootleg on different hardware */
	DRIVER( mrgoemon )	/* GX621 (c) 1986 (Japan) */
	DRIVER( jailbrek )	/* GX507 (c) 1986 */
	DRIVER( manhatan )	/* GX507 (c) 1986 (Japan) */
   	DRIVER( jailbrekb )	/* bootleg */
	DRIVER( scotrsht )	/* GX545 (c) 1985 */
	DRIVER( finalizr )	/* GX523 (c) 1985 */
	DRIVER( finalizrb )	/* bootleg */
	DRIVER( ironhors )	/* GX560 (c) 1986 */
	DRIVER( dairesya )	/* GX560 (c) 1986 (Japan) */
	DRIVER( farwest )	/* bootleg */
	DRIVER( jackal )	/* GX631 (c) 1986 (World) */
	DRIVER( topgunr )	/* GX631 (c) 1986 (US) */
	DRIVER( jackalj )	/* GX631 (c) 1986 (Japan) */
	DRIVER( topgunbl )	/* bootleg */
	DRIVER( ddribble )	/* GX690 (c) 1986 */
	DRIVER( contra )	/* GX633 (c) 1987 */
	DRIVER( contra1 )	/* GX633 (c) 1987 */
	DRIVER( contrab )	/* bootleg */
	DRIVER( contraj )	/* GX633 (c) 1987 (Japan) */
	DRIVER( contrajb )	/* bootleg */
	DRIVER( gryzor )	/* GX633 (c) 1987 */
	DRIVER( gryzora )	/* GX633 (c) 1987 */
	DRIVER( combasc )	/* GX611 (c) 1988 */
	DRIVER( combasct )	/* GX611 (c) 1987 */
	DRIVER( combascj )	/* GX611 (c) 1987 (Japan) */
	DRIVER( bootcamp )	/* GX611 (c) 1987 */
	DRIVER( combascb )	/* bootleg */
	DRIVER( rockrage )	/* GX620 (c) 1986 (World?) */
	DRIVER( rockragea )	/* GX620 (c) 1986 (Prototype?) */
	DRIVER( rockragej )	/* GX620 (c) 1986 (Japan) */
	DRIVER( mx5000 )	/* GX669 (c) 1987 */
	DRIVER( flkatck )	/* GX669 (c) 1987 (Japan) */
	DRIVER( fastlane )	/* GX752 (c) 1987 */
	DRIVER( tricktrp )	/* GX771 (c) 1987 */
	DRIVER( labyrunr )	/* GX771 (c) 1987 (Japan) */
	DRIVER( labyrunrk )	/* GX771 (c) 1987 (Japan) */
	DRIVER( thehustl )	/* GX765 (c) 1987 (Japan) */
	DRIVER( thehustlj )	/* GX765 (c) 1987 (Japan) */
	DRIVER( rackemup )	/* GX765 (c) 1987 */
	DRIVER( battlnts )	/* GX777 (c) 1987 */
	DRIVER( battlntsj )	/* GX777 (c) 1987 (Japan) */
	DRIVER( bladestl )	/* GX797 (c) 1987 */
	DRIVER( bladestle )	/* GX797 (c) 1987 */
	DRIVER( hcastle )	/* GX768 (c) 1988 */
	DRIVER( hcastleo )	/* GX768 (c) 1988 */
	DRIVER( hcastlej )	/* GX768 (c) 1988 (Japan) */
	DRIVER( hcastljo )	/* GX768 (c) 1988 (Japan) */
	DRIVER( ajax )		/* GX770 (c) 1987 */
	DRIVER( typhoon )	/* GX770 (c) 1987 */
	DRIVER( ajaxj )		/* GX770 (c) 1987 (Japan) */
	DRIVER( scontra )	/* GX775 (c) 1988 */
	DRIVER( scontraj )	/* GX775 (c) 1988 (Japan) */
	DRIVER( thunderx )	/* GX873 (c) 1988 */
	DRIVER( thunderxa )	/* GX873 (c) 1988 */
	DRIVER( thunderxb )	/* GX873 (c) 1988 */
	DRIVER( thunderxj )	/* GX873 (c) 1988 (Japan) */
	DRIVER( mainevt )	/* GX799 (c) 1988 */
	DRIVER( mainevto )	/* GX799 (c) 1988 */
	DRIVER( mainevt2p )	/* GX799 (c) 1988 */
	DRIVER( ringohja )	/* GX799 (c) 1988 (Japan) */
	DRIVER( devstors )	/* GX890 (c) 1988 */
	DRIVER( devstors2 )	/* GX890 (c) 1988 */
	DRIVER( devstors3 )	/* GX890 (c) 1988 */
	DRIVER( garuka )	/* GX890 (c) 1988 (Japan) */
	DRIVER( 88games )	/* GX861 (c) 1988 */
	DRIVER( konami88 )	/* GX861 (c) 1988 */
	DRIVER( hypsptsp )	/* GX861 (c) 1988 (Japan) */
	DRIVER( gbusters )	/* GX878 (c) 1988 */
	DRIVER( gbustersa )	/* GX878 (c) 1988 */
	DRIVER( crazycop )	/* GX878 (c) 1988 (Japan) */
	DRIVER( crimfght )	/* GX821 (c) 1989 (US) */
	DRIVER( crimfght2 )	/* GX821 (c) 1989 (World) */
	DRIVER( crimfghtj )	/* GX821 (c) 1989 (Japan) */
	DRIVER( spy )		/* GX857 (c) 1989 (World) */
	DRIVER( spyu )		/* GX857 (c) 1989 (US) */
	DRIVER( bottom9 )	/* GX891 (c) 1989 */
	DRIVER( bottom9n )	/* GX891 (c) 1989 */
	DRIVER( mstadium )	/* GX891 (c) 1989 (Japan) */
	DRIVER( blockhl )	/* GX973 (c) 1989 */
	DRIVER( quarth )	/* GX973 (c) 1989 (Japan) */
	DRIVER( aliens )	/* GX875 (c) 1990 (World) */
	DRIVER( aliens2 )	/* GX875 (c) 1990 (World) */
	DRIVER( aliens3 )	/* GX875 (c) 1990 (World) */
	DRIVER( aliensu )	/* GX875 (c) 1990 (US) */
	DRIVER( aliensj )	/* GX875 (c) 1990 (Japan) */
	DRIVER( aliensj2 )	/* GX875 (c) 1990 (Japan) */
	DRIVER( aliensa )	/* GX875 (c) 1990 (Asia) */
	DRIVER( suratk )	/* GX911 (c) 1990 (World) */
	DRIVER( suratka )	/* GX911 (c) 1990 (Asia) */
	DRIVER( suratkj )	/* GX911 (c) 1990 (Japan) */
	DRIVER( parodius )	/* GX955 (c) 1990 (World) */
	DRIVER( parodiusj )	/* GX955 (c) 1990 (Japan) */
	DRIVER( rollerg )	/* GX999 (c) 1991 (US) */
	DRIVER( rollergj )	/* GX999 (c) 1991 (Japan) */
	DRIVER( simpsons )	/* GX072 (c) 1991 */
	DRIVER( simpsons4pa )	/* GX072 (c) 1991 */
	DRIVER( simpsons2p )	/* GX072 (c) 1991 */
	DRIVER( simpsons2p2 )	/* GX072 (c) 1991 */
	DRIVER( simpsons2pa )	/* GX072 (c) 1991 (Asia) */
	DRIVER( simpsons2pj )	/* GX072 (c) 1991 (Japan) */
	DRIVER( esckids )	/* GX975 (c) 1991 (Asia) */
	DRIVER( esckidsj )	/* GX975 (c) 1991 (Japan) */
	DRIVER( vendetta )	/* GX081 (c) 1991 (World) */
	DRIVER( vendettar )	/* GX081 (c) 1991 (World) */
	DRIVER( vendetta2p )/* GX081 (c) 1991 (World) */
	DRIVER( vendetta2pu )/* GX081 (c) 1991 (Asia) */
	DRIVER( vendetta2pd )/* GX081 (c) 1991 (Asia) */
	DRIVER( vendettaj )	/* GX081 (c) 1991 (Japan) */
	DRIVER( mogura )	/* GX141 (c) 1991 */
	DRIVER( wecleman )	/* GX602 (c) 1986 */
	DRIVER( hotchase )	/* GX763 (c) 1988 */
	DRIVER( chqflag )	/* GX717 (c) 1988 */
	DRIVER( chqflagj )	/* GX717 (c) 1988 (Japan) */
	DRIVER( ultraman )	/* GX910 (c) 1991 Banpresto/Bandai */
	DRIVER( hexion )	/* GX122 (c) 1992 */
	DRIVER( lethalen )	/* GX191 (c) 1992 */
	DRIVER( lethalenua )	/* GX191 (c) 1992 */
	DRIVER( lethalenux )	/* GX191 (c) 1992 */
	DRIVER( lethaleneab )	/* GX191 (c) 1992 */
	DRIVER( lethaleneae )	/* GX191 (c) 1992 */
	DRIVER( lethalenj )	/* GX191 (c) 1992 */
	DRIVER( tgtpanic )	/* GX601 (c) 1996 */

	/* Konami "Nemesis hardware" games */
	DRIVER( nemesis )	/* GX456 (c) 1985 */
	DRIVER( nemesisuk )	/* GX456 (c) 1985 */
	DRIVER( konamigt )	/* GX561 (c) 1985 */
	DRIVER( salamand )	/* GX587 (c) 1986 */
	DRIVER( salamandj )	/* GX587 (c) 1986 */
	DRIVER( lifefrce )	/* GX587 (c) 1986 (US) */
	DRIVER( lifefrcej )	/* GX587 (c) 1986 (Japan) */
	DRIVER( blkpnthr )	/* GX604 (c) 1987 (Japan) */
	DRIVER( citybomb )	/* GX787 (c) 1987 (World) */
	DRIVER( citybombj )	/* GX787 (c) 1987 (Japan) */
	DRIVER( kittenk )	/* GX712 (c) 1988 */
	DRIVER( nyanpani )	/* GX712 (c) 1988 (Japan) */
	DRIVER( hcrash )	/* GX790 (c) 1987 */
	DRIVER( hcrashc )	/* GX790 (c) 1987 */

	/* GX400 BIOS based games */
	DRIVER( rf2 )		/* GX561 (c) 1985 */
	DRIVER( twinbee )	/* GX412 (c) 1985 */
	DRIVER( gradius )	/* GX456 (c) 1985 */
	DRIVER( gwarrior )	/* GX578 (c) 1985 */

	/* Konami "Twin 16" games */
	DRIVER( devilw )	/* GX687 (c) 1987 */
	DRIVER( darkadv )	/* GX687 (c) 1987 */
	DRIVER( majuu )		/* GX687 (c) 1987 (Japan) */
	DRIVER( vulcan )	/* GX785 (c) 1988 */
	DRIVER( vulcana )	/* GX785 (c) 1988 */
	DRIVER( vulcanb )	/* GX785 (c) 1988 */
	DRIVER( gradius2 )	/* GX785 (c) 1988 (Japan) */
	DRIVER( gradius2a )	/* GX785 (c) 1988 (Japan) */
	DRIVER( gradius2b )	/* GX785 (c) 1988 (Japan) */
	DRIVER( cuebrickj )	/* GX903 (c) 1989 (Japan) */
	DRIVER( fround )	/* GX870 (c) 1988 */
	DRIVER( froundl )	/* GX870 (c) 1988 */
	DRIVER( hpuncher )	/* GX870 (c) 1988 (Japan) */
	DRIVER( miaj )		/* GX808 (c) 1989 (Japan) */

	/* (some) Konami 68000 games */
	DRIVER( cuebrick )	/* GX903 (c) 1989 */
	DRIVER( mia )		/* GX808 (c) 1989 */
	DRIVER( mia2 )		/* GX808 (c) 1989 */
	DRIVER( tmnt )		/* GX963 (c) 1989 (World) */
	DRIVER( tmntu )		/* GX963 (c) 1989 (US) */
	DRIVER( tmntua )	/* GX963 (c) 1989 (US) */
	DRIVER( tmht )		/* GX963 (c) 1989 (UK) */
	DRIVER( tmntj )		/* GX963 (c) 1990 (Japan) */
	DRIVER( tmht2p )	/* GX963 (c) 1989 (UK) */
	DRIVER( tmht2pa )	/* GX963 (c) 1989 (UK) */
	DRIVER( tmnt2pj )	/* GX963 (c) 1990 (Japan) */
	DRIVER( tmnt2po )	/* GX963 (c) 1989 (Oceania) */
	DRIVER( punkshot )	/* GX907 (c) 1990 (US) */
	DRIVER( punkshot2 )	/* GX907 (c) 1990 (US) */
	DRIVER( punkshotj )	/* GX907 (c) 1990 (Japan) */
	DRIVER( lgtnfght )	/* GX939 (c) 1990 (World) */
	DRIVER( lgtnfghta )	/* GX939 (c) 1990 (Asia) */
	DRIVER( lgtnfghtu )	/* GX939 (c) 1990 (US) */
	DRIVER( trigon )	/* GX939 (c) 1990 (Japan) */
	DRIVER( blswhstl )	/* GX060 (c) 1991 */
	DRIVER( detatwin )	/* GX060 (c) 1991 (Japan) */
	DRIVER( glfgreat )	/* GX061 (c) 1991 */
	DRIVER( glfgreatj )	/* GX061 (c) 1991 (Japan) */
	DRIVER( tmnt2 )		/* GX063 (c) 1991 (US) */
	DRIVER( tmnt2a )	/* GX063 (c) 1991 (Asia) */
	DRIVER( tmht22pe )	/* GX063 (c) 1991 (UK) */
	DRIVER( tmnt22pu )	/* GX063 (c) 1991 (US) */
	DRIVER( ssriders )	/* GX064 (c) 1991 (World) */
	DRIVER( ssridersebd )	/* GX064 (c) 1991 (World) */
	DRIVER( ssridersebc )	/* GX064 (c) 1991 (World) */
	DRIVER( ssridersuda )	/* GX064 (c) 1991 (US) */
	DRIVER( ssriderseaa )	/* GX064 (c) 1991 (US) */
	DRIVER( ssridersuac )	/* GX064 (c) 1991 (US) */
	DRIVER( ssridersubc )	/* GX064 (c) 1991 (US) */
	DRIVER( ssridersabd )	/* GX064 (c) 1991 (Asia) */
	DRIVER( ssridersadd )	/* GX064 (c) 1991 (Asia) */
	DRIVER( ssridersjbd )	/* GX064 (c) 1991 (Japan) */
	DRIVER( ssridersb )	/* bootleg */
	DRIVER( xmen )		/* GX065 (c) 1992 (US) */
	DRIVER( xmenj )		/* GX065 (c) 1992 (Japan) */
	DRIVER( xmen2pe )	/* GX065 (c) 1992 (World) */
	DRIVER( xmen2pa )	/* GX065 (c) 1992 (Asia) */
	DRIVER( xmen2pj )	/* GX065 (c) 1992 (Japan) */
	DRIVER( xmen6p )	/* GX065 (c) 1992 */
	DRIVER( xmen6pu )	/* GX065 (c) 1992 */
	DRIVER( xexex )		/* GX067 (c) 1991 (World) */
	DRIVER( xexexa )	/* GX067 (c) 1991 (AAA) */
	DRIVER( xexexj )	/* GX067 (c) 1991 (Japan) */
	DRIVER( asterix )	/* GX068 (c) 1992 (World) */
	DRIVER( asterixeac )	/* GX068 (c) 1992 (World) */
	DRIVER( asterixeaa )	/* GX068 (c) 1992 (World) */
	DRIVER( asterixj )	/* GX068 (c) 1992 (Japan) */
	DRIVER( gijoe )		/* GX069 (c) 1991 (World) */
	DRIVER( gijoeu )	/* GX069 (c) 1991 (US) */
	DRIVER( gijoej )	/* GX069 (c) 1991 (Japan) */
	DRIVER( thndrx2 )	/* GX073 (c) 1991 (World) */
	DRIVER( thndrx2a )	/* GX073 (c) 1991 (Asia) */
	DRIVER( thndrx2j )	/* GX073 (c) 1991 (Japan) */
	DRIVER( prmrsocr )	/* GX101 (c) 1993 (Europe) */
	DRIVER( prmrsocrj )	/* GX101 (c) 1993 (Japan) */
	DRIVER( qgakumon )	/* GX248 (c) 1993 (Japan) */
	DRIVER( moo )		/* GX151 (c) 1992 (World) */
	DRIVER( mooua )		/* GX151 (c) 1992 (US) */
	DRIVER( mooaa )		/* GX151 (c) 1992 (US) */
	DRIVER( moobl )		/* bootleg */
	DRIVER( bucky )		/* GX173 (c) 1992 (World) */
	DRIVER( buckyua )	/* GX173 (c) 1992 (US) */
	DRIVER( buckyaa )	/* GX173 (c) 1992 (Asia) */
	DRIVER( gaiapols )	/* GX123 (c) 1993 (Europe) */
	DRIVER( gaiapolsu )	/* GX123 (c) 1993 (US) */
	DRIVER( gaiapolsj )	/* GX123 (c) 1993 (Japan) */
	DRIVER( mystwarr )	/* GX128 (c) 1993 (World) */
	DRIVER( mystwarru )	/* GX128 (c) 1993 (US) */
	DRIVER( mystwarrj )	/* GX128 (c) 1993 (Japan) */
	DRIVER( viostorm )	/* GX168 (c) 1993 (Europe) */
	DRIVER( viostormu )	/* GX168 (c) 1993 (US) */
	DRIVER( viostormub )	/* GX168 (c) 1993 (US) */
	DRIVER( viostormj )	/* GX168 (c) 1993 (Japan) */
	DRIVER( viostorma )	/* GX168 (c) 1993 (Asia) */
	DRIVER( mmaulers )	/* GX170 (c) 1993 (Europe) */
	DRIVER( dadandrn )	/* GX170 (c) 1993 (Japan) */
	DRIVER( metamrph )	/* GX224 (c) 1993 (Europe) */
	DRIVER( metamrphu )	/* GX224 (c) 1993 (US) */
	DRIVER( metamrphj )	/* GX224 (c) 1993 (Japan) */
	DRIVER( mtlchamp )	/* GX234 (c) 1993 (World) */
	DRIVER( mtlchamp1 )	/* GX234 (c) 1993 (World) */
	DRIVER( mtlchampu )	/* GX234 (c) 1993 (US) */
	DRIVER( mtlchampj )	/* GX234 (c) 1993 (Japan) */
	DRIVER( mtlchampa )	/* GX234 (c) 1993 (Japan) */
	DRIVER( rungun )	/* GX247 (c) 1993 (World) */
	DRIVER( runguna )	/* GX247 (c) 1993 (World) */
	DRIVER( rungunu )	/* GX247 (c) 1993 (US) */
	DRIVER( rungunua )	/* GX247 (c) 1993 (US) */
	DRIVER( slmdunkj )	/* GX247 (c) 1993 (Japan) */
	DRIVER( dbz )		/* (c) 1993 Banpresto */
	DRIVER( dbz2 )		/* (c) 1994 Banpresto */
	DRIVER( bishi )		/* GX575 (c) 1996 (Japan) */
	DRIVER( sbishi )	/* GX675 (c) 1998 (Japan) */
	DRIVER( sbishik )	/* GX675 (c) 1998 (Korea) */

	/* Konami dual 68000 games */
	DRIVER( overdriv )	/* GX789 (c) 1990 */
	DRIVER( gradius3 )	/* GX945 (c) 1989 (Japan) */
	DRIVER( gradius3a )	/* GX945 (c) 1989 (Asia) */
	DRIVER( gradius3e )	/* GX945 (c) 1989 (World?) */

	/* Konami 68020 games */
	DRIVER( plygonet )	/* GX305 (c) 1993 */
	DRIVER( polynetw )	/* GX305 too? (c) 1993 */

	/* Konami System GX games */
	DRIVER( konamigx )

	/* Williams games */
	DRIVER( defender )	/* (c) 1980 */
	DRIVER( defenderg )	/* (c) 1980 */
	DRIVER( defenderb )	/* (c) 1980 */
	DRIVER( defenderw )	/* (c) 1980 */
	DRIVER( defndjeu )	/* bootleg */
	DRIVER( tornado1 )	/* bootleg */
	DRIVER( tornado2 )	/* bootleg */
	DRIVER( zero )		/* bootleg */
	DRIVER( zero2 )		/* bootleg */
	DRIVER( defcmnd )	/* bootleg */
	DRIVER( defence )	/* bootleg */
	DRIVER( startrkd )	/* bootleg */
	DRIVER( mayday )	/* bootleg */
	DRIVER( maydaya )	/* bootleg */
	DRIVER( maydayb )	/* bootleg */
	DRIVER( colony7 )	/* (c) 1981 Taito */
	DRIVER( colony7a )	/* (c) 1981 Taito */
	DRIVER( jin )		/* Falcon bootleg/hack */
	DRIVER( stargate )	/* (c) 1981 */
	DRIVER( robotron )	/* (c) 1982 */
	DRIVER( robotronyo )/* (c) 1982 */
	DRIVER( joust )		/* (c) 1982 */
	DRIVER( joustr )	/* (c) 1982 */
	DRIVER( joustwr )	/* (c) 1982 */
	DRIVER( bubbles )	/* (c) 1982 */
	DRIVER( bubblesr )	/* (c) 1982 */
	DRIVER( bubblesp )	/* (c) 1982 */
	DRIVER( splat )		/* (c) 1982 */
	DRIVER( sinistar )	/* (c) 1982 */
	DRIVER( sinistar1 )	/* (c) 1982 */
	DRIVER( sinistar2 )	/* (c) 1982 */
	DRIVER( playball )	/* (c) 1983 */
	DRIVER( blaster )	/* (c) 1983 */
	DRIVER( blaster30 )	/* (c) 1983 */
	DRIVER( blasterkit )	/* (c) 1983 */
	DRIVER( spdball )	/* (c) 1985 */
	DRIVER( alienar )	/* (c) 1985 Duncan Brown */
	DRIVER( alienaru )	/* (c) 1985 Duncan Brown */
	DRIVER( mysticm )	/* (c) 1983 */
	DRIVER( tshoot )	/* (c) 1984 */
	DRIVER( inferno )	/* (c) 1984 */
	DRIVER( joust2 )	/* (c) 1986 */
	DRIVER( lottofun )	/* (c) 1987 H.A.R. Management */

	/* Capcom games */
	/* The following is a COMPLETE list of the Capcom games up to 1997, as shown on */
	/* their web site. The list is sorted by production date.                       */
	/* A comprehensive list of Capcom games with board info can be found here:      */
	/* http://www.arcadeflyers.com/strider/capcom_list.html                         */
	DRIVER( vulgus )	/*  5/1984 (c) 1984 */
	DRIVER( vulgus2 )	/*  5/1984 (c) 1984 */
	DRIVER( vulgusj )	/*  5/1984 (c) 1984 */
	DRIVER( sonson )	/*  7/1984 (c) 1984 */
	DRIVER( sonsonj )	/*  7/1984 (c) 1984 (Japan) */
	DRIVER( higemaru )	/*  9/1984 (c) 1984 */
	DRIVER( 1942 )		/* 12/1984 (c) 1984 */
	DRIVER( 1942a )		/* 12/1984 (c) 1984 */
	DRIVER( 1942abl )	/* bootleg */
	DRIVER( 1942b )		/* 12/1984 (c) 1984 */
	DRIVER( 1942w )		/* 12/1984 (c) 1984 + Williams Electronics license (c) 1985 */
	DRIVER( exedexes )	/*  2/1985 (c) 1985 */
	DRIVER( savgbees )	/*  2/1985 (c) 1985 + Memetron license */
	DRIVER( commando )	/*  5/1985 (c) 1985 (World) */
	DRIVER( commandou )	/*  5/1985 (c) 1985 + Data East license (US) */
	DRIVER( commandoj )	/*  5/1985 (c) 1985 (Japan) */
	DRIVER( commandob )	/* bootleg */
	DRIVER( sinvasn )	/* Europe original? */
	DRIVER( sinvasnb )	/* bootleg */
	DRIVER( gng )		/*  9/1985 (c) 1985 */
	DRIVER( gnga )		/*  9/1985 (c) 1985 */
	DRIVER( gngbl )		/* bootleg */
	DRIVER( gngblita )	/* bootleg */
	DRIVER( gngt )		/*  9/1985 (c) 1985 */
	DRIVER( makaimur )	/*  9/1985 (c) 1985 */
	DRIVER( makaimurc )	/*  9/1985 (c) 1985 */
	DRIVER( makaimurg )	/*  9/1985 (c) 1985 */
	DRIVER( diamond )	/* (c) 1989 KH Video (NOT A CAPCOM GAME but runs on GnG hardware) */
	DRIVER( gunsmoke )	/* 11/1985 (c) 1985 (World) */
	DRIVER( gunsmokeu )	/* 11/1985 (c) 1985 + Romstar (US) */
	DRIVER( gunsmokeua )/* 11/1985 (c) 1985 (US) */
	DRIVER( gunsmokej )	/* 11/1985 (c) 1985 (Japan) */
	DRIVER( sectionz )	/* 12/1985 (c) 1985 */
	DRIVER( sectionza )	/* 12/1985 (c) 1985 */
	DRIVER( trojan )	/*  4/1986 (c) 1986 (US) */
	DRIVER( trojanr )	/*  4/1986 (c) 1986 + Romstar */
	DRIVER( trojanj )	/*  4/1986 (c) 1986 (Japan) */
	DRIVER( srumbler )	/*  9/1986 (c) 1986 */
	DRIVER( srumbler2 )	/*  9/1986 (c) 1986 */
	DRIVER( rushcrsh )	/*  9/1986 (c) 1986 */
	DRIVER( lwings )	/* 11/1986 (c) 1986 */
	DRIVER( lwings2 )	/* 11/1986 (c) 1986 */
	DRIVER( lwingsj )	/* 11/1986 (c) 1986 */
	DRIVER( lwingsb )	/* 11/1986 (c) 1986 (bootleg)*/
	DRIVER( sidearms )	/* 12/1986 (c) 1986 (World) */
	DRIVER( sidearmsr )	/* 12/1986 (c) 1986 + Romstar license (US) */
	DRIVER( sidearmsj )	/* 12/1986 (c) 1986 (Japan) */
	DRIVER( turtship )	/* (c) 1988 Philco (NOT A CAPCOM GAME but runs on modified Sidearms hardware) */
	DRIVER( turtshipj )	/* (c) 1988 Philco (NOT A CAPCOM GAME but runs on modified Sidearms hardware) */
	DRIVER( turtshipk )	/* (c) 1988 Philco (NOT A CAPCOM GAME but runs on modified Sidearms hardware) */
	DRIVER( dyger )		/* (c) 1989 Philco (NOT A CAPCOM GAME but runs on modified Sidearms hardware) */
	DRIVER( dygera )	/* (c) 1989 Philco (NOT A CAPCOM GAME but runs on modified Sidearms hardware) */
	DRIVER( twinfalc )	/* (c) 1989 Philko (Poara Enterprises license) (NOT A CAPCOM GAME but runs on modified Sidearms hardware) */
	DRIVER( whizz )		/* (c) 1989 Philco (NOT A CAPCOM GAME but runs on modified Sidearms hardware) */
	DRIVER( avengers )	/*  2/1987 (c) 1987 (US) */
	DRIVER( avengers2 )	/*  2/1987 (c) 1987 (US) */
	DRIVER( buraiken )	/*  2/1987 (c) 1987 (Japan) */
	DRIVER( bionicc )	/*  3/1987 (c) 1987 (Euro) */
	DRIVER( bionicc1 )	/*  3/1987 (c) 1987 (US) */
	DRIVER( bionicc2 )	/*  3/1987 (c) 1987 (US) */
	DRIVER( topsecrt )	/*  3/1987 (c) 1987 (Japan) */
	DRIVER( 1943 )		/*  6/1987 (c) 1987 (US) */
	DRIVER( 1943j )		/*  6/1987 (c) 1987 (Japan) */
	DRIVER( blktiger )	/*  8/1987 (c) 1987 (US) */
	DRIVER( blktigerb1 )/* bootleg */
	DRIVER( blktigerb2 )/* bootleg */
	DRIVER( blkdrgon )	/*  8/1987 (c) 1987 (Japan) */
	DRIVER( blkdrgonb )	/* bootleg, hacked to say Black Tiger */
	DRIVER( sf )		/*  8/1987 (c) 1987 (World) */
	DRIVER( sfus )		/*  8/1987 (c) 1987 (US) */
	DRIVER( sfj )		/*  8/1987 (c) 1987 (Japan) */
	DRIVER( sfp )		/*  8/1987 (c) 1987 */
	DRIVER( tigeroad )	/* 11/1987 (c) 1987 + Romstar (US) */
	DRIVER( toramich )	/* 11/1987 (c) 1987 (Japan) */
	DRIVER( tigeroadb )	/* bootleg */
	DRIVER( f1dream )	/*  4/1988 (c) 1988 + Romstar */
	DRIVER( f1dreamb )	/* bootleg */
	DRIVER( 1943kai )	/*  6/1988 (c) 1987 (Japan) */
	DRIVER( lastduel )	/*  7/1988 (c) 1988 (US) */
	DRIVER( lastduelo )	/*  7/1988 (c) 1988 (US) */
	DRIVER( lastduelb )	/* bootleg */
	DRIVER( madgear )	/*  2/1989 (c) 1989 (US) */
	DRIVER( madgearj )	/*  2/1989 (c) 1989 (Japan) */
	DRIVER( ledstorm )	/*  1988 (c) 1988 (US) */
	DRIVER( ledstorm2 )	/*  1988 (c) 1988 (US) */
	/*  3/1989 Dokaben (baseball) - see below among "Mitchell" games */
	/*  8/1989 Dokaben 2 (baseball) - see below among "Mitchell" games */
	/* 10/1989 Capcom Baseball - see below among "Mitchell" games */
	/* 11/1989 Capcom World - see below among "Mitchell" games */
	/*  3/1990 Adventure Quiz 2 Hatena no Dai-Bouken - see below among "Mitchell" games */
	/*  1/1991 Quiz Tonosama no Yabou - see below among "Mitchell" games */
	/*  4/1991 Ashita Tenki ni Naare (golf) - see below among "Mitchell" games */
	/*  5/1991 Ataxx - see below among "Leland" games */
	/*  6/1991 Quiz Sangokushi - see below among "Mitchell" games */
	/* 10/1991 Block Block - see below among "Mitchell" games */
	/*  6/1995 Street Fighter - the Movie - see below among "Incredible Technologies" games */

	/* Sega System E games (Master System hardware) */
	DRIVER( hangonjr )	/* (c) 1985 */
	DRIVER( transfrm )	/* 834-5803 (c) 1986 */
	DRIVER( astrofl )	/* 834-5803 (c) 1986 */
	DRIVER( ridleofp )	/* (c) 1986 Sega / Nasco */
	DRIVER( fantzn2 )	/* (c) 1988 */
	DRIVER( opaopa )
	DRIVER( tetrisse )	/* (c) 1988 */

	/* other Sega 8-bit games */
	DRIVER( turbo )		/* (c) 1981 Sega */
	DRIVER( turboa )	/* (c) 1981 Sega */
	DRIVER( turbob )	/* (c) 1981 Sega */
	DRIVER( subroc3d )	/* (c) 1982 Sega */
	DRIVER( buckrog )	/* (c) 1982 Sega */
	DRIVER( buckrogn )	/* (c) 1982 Sega */
	DRIVER( zoom909 )	/* (c) 1982 Sega */
	DRIVER( kopunch )	/* 834-0103 (c) 1981 Sega */
	DRIVER( suprloco )	/* (c) 1982 Sega */
	DRIVER( suprlocoa )	/* (c) 1982 Sega */
	DRIVER( dotrikun )	/* cabinet test board */
	DRIVER( dotrikun2 )	/* cabinet test board */
	DRIVER( spcpostn )	/* (c) 1986 Sega / Nasco" */
	DRIVER( angelkds )	/* 833-6599 (c) 1988 Sega / Nasco? */
	DRIVER( calorie )	/* (c) 1986 Sega */
	DRIVER( calorieb )	/* (c) 1986 Sega (but bootleg) */

	/* Bingo-based games */
	DRIVER( bingoc )	/* (c) 1989 Sega */
	/* Bingo Fantasy  *//* (c) 19?? Sega */
	/* Bingo Star     *//* (c) 19?? Sega */
	/* Bingo Party    *//* (c) 1993 Sega */
	/* BP Phoenix     *//* (c) 1998 Sega */
	/* BP Special     *//* (c) 2000 Sega */
	/* BP Multicards  *//* (c) 2002 Sega */
	/* BP Splash      *//* (c) 2002 Sega */
	/* Bingo Planet   *//* (c) 1997 Sega */

	/* Enduro Racer / Space Harrier / Hang On */
	DRIVER( enduror )	/* (c) 1985 (FD1089B, decrypted) */
	DRIVER( enduror1 )	/* (c) 1985 (FD1089B, decrypted) */
	DRIVER( endurob2 )	/* (c) 1985 (Beta bootleg) */
	DRIVER( endurobl )	/* (c) 1985 (Herb bootleg) */
	DRIVER( hangon )	/* (c) 1985 (Rev A)*/
	DRIVER( hangon1 )	/* (c) 1985 */
	DRIVER( sharrier )	/* (c) 1985 */
	DRIVER( sharrier1 )	/* (c) 1985 */
	DRIVER( shangonro )	/* (c) 1987 (FD1094, decrypted) */
	DRIVER( shangonrb )	/* (c) 1992 (but bootleg, hangon hw?) */

	/* Pre-16 */
	DRIVER( aliensynjo )	/* (c) 1987 (FD1089A, decrypted) */
	DRIVER( aliensyn2 )	/* (c) 1987 (FD1089A, decrypted) */
	DRIVER( aliensyn5 )	/* (c) 1987 (FD1089B) */
	DRIVER( bodyslam )	/* (c) 1986 (8751) */
	DRIVER( dumpmtmt )	/* (c) 1986 (Japan) */
	DRIVER( mjleague )	/* (c) 1985 */
	DRIVER( quartet )	/* (c) 1986 (8751) */
	DRIVER( quarteta )	/* (c) 1986 (8751) */
	DRIVER( quartet2 )	/* (c) 1986 (8751) */
	DRIVER( quartet2a )	/* (c) 1986 */

	/* System16A */
	DRIVER( aceattaca )	/* (c) 1988 (FD1094, decrypted) */
	DRIVER( afighter )	/* (c) 1986 (FD1089A, decrypted) */
	DRIVER( alexkidd )	/* (c) 1986 (FD1089A, decrypted) */
	DRIVER( alexkidd1 )	/* (c) 1986 */
	DRIVER( fantzone )	/* (c) 1986 */
	DRIVER( fantzone1 )	/* (c) 1986 */
	DRIVER( sdi )		/* (c) 1987 (FD1089B, decrypted) */
	DRIVER( shinobi )	/* (c) 1987 */
	DRIVER( shinobi1 )	/* (c) 1987 (FD1094, decrypted) */
	DRIVER( shinobls )	/* (c) 1987 (Star bootleg) */
	DRIVER( sjryuko1 )	/* (c) 1988 White Board (FD1089B, decrypted) */
	DRIVER( tetris )	/* (c) 1988 (FD1094, decrypted) S16A */
	DRIVER( tetris3 )	/* (c) 1988 (FD1094, decrypted) S16A */
	DRIVER( timescan1 )	/* (c) 1987 (FD1089B, decrypted) */
	DRIVER( wb31 )		/* (c) 1988 Sega / Westone (FD1094, decrypted) */
	DRIVER( wb35 )		/* (c) 1988 Sega / Westone (FD1089A, decrypted) */
	DRIVER( passsht16a )/* (c) 1988 */

	/* System 16B */
	DRIVER( aceattac )	/* (c) 1988 (protected) */
	DRIVER( aliensyn )	/* (c) 1987 */
	DRIVER( aliensyn3 )	/* (c) 1987 (FD1089A, decrypted) */
	DRIVER( aliensynj )	/* (c) 1987 (FD1089A, decrypted) */
	DRIVER( altbeast )	/* (c) 1988 (8751) */
	DRIVER( altbeastj )	/* (c) 1988 (8751) */
	DRIVER( altbeast5 )	/* (c) 1988 (8751) */
	DRIVER( altbeast4 )	/* (c) 1988 (MC-8123B) */
	DRIVER( altbeastj3 )	/* (c) 1988 (FD1094, decrypted) */
	DRIVER( altbeast2 )	/* (c) 1988 (MC-8123B) */
	DRIVER( altbeastj1 )	/* (c) 1988 (protected) */
	DRIVER( aurail )	/* (c) 1990 Sega / Westone */
	DRIVER( aurail1 )	/* (c) 1990 Sega / Westone (FD1089B, decrypted) */
	DRIVER( aurailj )	/* (C) 1990 Sega / Westone (FD1089A, decrypted) */
	DRIVER( bayroute )	/* (c) 1989 Sunsoft / Sega (FD1094, decrypted) */
	DRIVER( bayroutej )	/* (c) 1989 Sunsoft / Sega (FD1094, decrypted) */
	DRIVER( bayroute1 )	/* (c) 1989 Sunsoft / Sega */
	DRIVER( bullet )	/* (c) 1987 (protected) */
	DRIVER( cotton )	/* (c) 1990 (FD1094, decrypted) */
	DRIVER( cottonu )	/* (c) 1990 (FD1094, decrypted) */
	DRIVER( cottonj )	/* (c) 1990 (FD1094, decrypted) */
	DRIVER( ddux )		/* (c) 1989 (FD1094, decrypted) */
	DRIVER( ddux1 )		/* (c) 1989 (8751) */
	DRIVER( dunkshot )	/* (c) 1986 (FD1094, decrypted) */
	DRIVER( eswat )		/* (c) 1989 (FD1094, decrypted) */
	DRIVER( eswatu )	/* (c) 1989 (FD1094, decrypted) */
	DRIVER( eswatj )	/* (c) 1989 (FD1094, decrypted) */
	DRIVER( exctleag )	/* (protected) */
	DRIVER( fpoint )	/* (c) 1989 (Japan, FD1094, decrypted) */
	DRIVER( fpoint1 )	/* (c) 1989 (Japan, FD1094, decrypted) */
	DRIVER( goldnaxe )	/* (c) 1989 (8751) */
	DRIVER( goldnaxeu )	/* (c) 1989 (protected) */
	DRIVER( goldnaxej )	/* (c) 1989 (FD1094, decrypted) */
	DRIVER( goldnaxe3 )	/* (c) 1989 (FD1094, decrypted) */
	DRIVER( goldnaxe2 )	/* (c) 1989 (8751) */
	DRIVER( goldnaxe1 )	/* (c) 1989 (FD1094, decrypted) */
	DRIVER( hwchamp )	/* (c) 1987 */
	DRIVER( mvp )		/* (c) 1989 (FD1094, decrypted) */
	DRIVER( mvpj )		/* (c) 1989 (FD1094, decrypted) */
	DRIVER( passsht )	/* (c) 1988 (FD1094, decrypted) */
	DRIVER( passshta )	/* (c) 1988 (FD1094, decrypted) */
	DRIVER( passshtj )	/* (c) 1988 (FD1094, decrypted) */
	DRIVER( riotcity )	/* (c) 1991 Sega / Westone */
	DRIVER( ryukyu )	/* (c) 1990 (FD1094, decrypted) */
	DRIVER( sdib )		/* (c) 1987 (FD1089A, decrypted) */
	DRIVER( sdibl )		/* (c) 1987 bootleg */
	DRIVER( defense )	/* (c) 1987 (FD1094, decrypted) */
	DRIVER( shinobi5 )	/* (c) 1987 */
	DRIVER( shinobi4 )	/* (c) 1987 (MC-8123B) */
	DRIVER( shinobi3 )	/* (c) 1987 (MC-8123B) */
	DRIVER( shinobi2 )	/* (c) 1987 (FD1094, decrypted) */
	DRIVER( sonicbom )	/* (c) 1987 (FD1094, decrypted) */
	DRIVER( sjryuko )	/* (c) 1988 White Board (FD1094, decrypted) */
	DRIVER( suprleag )	/* (c) 1987 (protected) */
	DRIVER( tetris2 )	/* (c) 1988 (FD1094, decrypted) S16B */
	DRIVER( tetris1 )	/* (c) 1988 (FD1094, decrypted) S16B */
	DRIVER( timescan )	/* (c) 1987 */
	DRIVER( toryumon )	/* (c) 1995 */
	DRIVER( tturf )		/* (c) 1989 Sega / Sunsoft (8751) */
	DRIVER( tturfu )	/* (c) 1989 Sega / Sunsoft (8751) */
	DRIVER( wb3 )		/* (c) 1988 Sega / Westone (8751) */
	DRIVER( wb34 )		/* (c) 1988 Sega / Westone (FD1094, decrypted) */
	DRIVER( wb33 )		/* (c) 1988 Sega / Westone (FD1094, decrypted) */
	DRIVER( wb32 )		/* (c) 1988 Sega / Westone (FD1094, decrypted) */
	DRIVER( wrestwar )	/* (c) 1989 (8751) */
	DRIVER( wrestwar2 )	/* (c) 1989 (FD1094, decrypted) */
	DRIVER( wrestwar1 )	/* (c) 1989 (FD1094, decrypted) */

	/* Philko Boards */
	DRIVER( atomicp )	/* (c) 1990 Philko - korean clone board */
	DRIVER( snapper )	/* (c) 1990 Philko - korean clone board */


	/* S16 Bootlegs */
	DRIVER( bayrouteb1 )/* (c) 1989 (protected) (bootleg) */
	DRIVER( bayrouteb2 )/* (c) 1989 (protected) (bootleg) */
	DRIVER( dduxbl )	/* (c) 1989 (Datsu bootleg) */
	DRIVER( eswatbl )	/* BOOTLEG */
	DRIVER( fpointbl )	/* (c) 1989 (Datsu bootleg) */
	DRIVER( fpointbj )	/* (c) 1989 (Datsu bootleg, Japan) */
	DRIVER( goldnaxeb1 )/* BOOTLEG  */
	DRIVER( goldnaxeb2 )/* BOOTLEG  */
	DRIVER( passht4b )	/* bootleg */
	DRIVER( passshtb )	/* bootleg */
	DRIVER( shinoblb )	/* (c) 1987 (but bootleg) */
	DRIVER( shinobld )	/* (c) 1987 (but bootleg) */
	DRIVER( tetrisbl )	/* (c) 1988 (but bootleg) */
	DRIVER( beautyb )	/* (c) 1991 AMT */
	DRIVER( iqpipe )	/* (c) 1991 AMT */
	DRIVER( tturfbl )	/* (c) 1989 (Datsu bootleg) */
	DRIVER( wb3bbl )	/* BOOTLEG */

	/* System 18 */
	DRIVER( shdancer )	/* 1989.05 Shadow Dancer (US) */
	DRIVER( shdancerj )	/* 1989.11 Shadow Dancer (Japan) */
	DRIVER( shdancer1 )	/* 1989.?? Shadow Dancer (World) */
	DRIVER( bloxeed )	/* 1989.12 Bloxeed (Japan, FD1094, decrypted) */
						/* 1990.04 Bloxeed (US) */
	DRIVER( astormu )	/* 1990.04 Alien Storm (US, FD1094, decrypted) */
	DRIVER( astormj )	/* 1990.05 Alien Storm (Japan, FD1094, decrypted) */
	DRIVER( astorm )	/* 1990.?? Alien Storm (World, protected 2 Players) */
	DRIVER( astorm3 )	/* 1990.?? Alien Storm (World, FD1094, decrypted) */
	DRIVER( mwalku )	/* 1990.08 Micheal Jackson's Moonwalker (US, FD1094+8751, decrypted) */
	DRIVER( mwalkj )	/* 1990.08 Micheal Jackson's Moonwalker (Japan, FD1094+8751, decrypted) */
	DRIVER( mwalk )		/* 1990.?? Micheal Jackson's Moonwalker (World, FD1094+8751, decrypted) */
	DRIVER( lghost )	/* 1990.?? Laser Ghost (World, FD1094, decrypted) */
						/* 1990.12 Laser Ghost (Japan) */
	DRIVER( lghostu )	/* 1991.01 Laser Ghost (US, FD1094, decrypted) */
	DRIVER( cltchitr )	/* 1991.02 Clutch Hitter (US, FD1094, decrypted) */
	DRIVER( cltchitrj )	/* 1991.05 Clutch Hitter (Japan, FD1094, decrypted) */
	DRIVER( ddcrewj )	/* 1991.07 D.D.Crew (Japan, FD1094, decrypted) */
	DRIVER( ddcrewu )	/* 1991.09 D.D.Crew (US, FD1094, decrypted) */
	DRIVER( ddcrew )	/* 1991.?? D.D.Crew (World, FD1094, decrypted) */
	DRIVER( ddcrew2 )	/* 1991.?? D.D.Crew (World, FD1094, decrypted) */
	DRIVER( ddcrew1 )	/* 1991.?? D.D.Crew (World, FD1094, decrypted) */
	DRIVER( wwallyj )	/* 1992.06 Wally wo Sagase! (Japan, FD1094, decrypted) */
	DRIVER( wwallyja )	/* 1992.06 Wally wo Sagase! (Japan, FD1094, decrypted) */
						/* 1992.10 Desert Breaker (Japan) */
	DRIVER( desertbr )	/* 1993.?? Desert Breaker (World, FD1094, decrypted) */
	DRIVER( pontoon )

	/* System18 Bootlegs */
	DRIVER( astormbl )	/* BOOTLEG */
	DRIVER( astormb2 )	/* BOOTLEG */
	DRIVER( shdancbl )	/* BOOTLEG */
	DRIVER( mwalkbl )	/* BOOTLEG */


	/* Outrun Hardware */
						/* 1986.09 Outrun (Japan) */
						/* 1986.11 Outrun (US) */
						/* 1986.?? Outrun (World) */
	DRIVER( outrun )	/* Revision B */
	DRIVER( outrunra )	/* Revision A */
	DRIVER( outruno )	/* First version */
	DRIVER( outrundx )	/* Deluxe version */
	DRIVER( outrunb )	/* 1986 (protected beta bootleg) */
						/* 1987.04 Super Hang-On (Japan) */
						/* 1987.06 Super Hang-On (US) */
						/* 1987.?? Super Hang-On (World) */
	DRIVER( shangon )	/* 1987 (protected) */
	DRIVER( shangon3 )	/* 1987 (FD1089B, decrypted) */
	DRIVER( shangon2 )	/* 1987 (FD1089B, decrypted) */
	DRIVER( shangon1 )	/* 1987 (FD1089B, decrypted) */
	DRIVER( shangonle )	/* 1991 */
						/* 1989.02 Turbo Outrun (Japan) */
						/* 1989.04 Turbo Outrun (US) */
						/* 1989.?? Turbo Outrun (World) */
	DRIVER( toutrun )	/* 1987 (FD1094, decrypted) */
	DRIVER( toutrun2 )	/* 1987 (FD1094, decrypted) */
	DRIVER( toutrun1 )	/* 1987 (protected) */
	DRIVER( toutrunu )	/* 1987 (FD1094, decrypted) */

	/* X Board */
	DRIVER( aburner )	/* 1987.07 After Burner (Japan) */
	DRIVER( aburner2 )	/* 1987.09 After Burner II (Japan) */
	DRIVER( thndrbld1 )	/* 1987.12 Thunder Blade (Japan, deluxe/standard) */
	DRIVER( thndrbld )	/* 1988.02 Thunder Blade (US?, upright, FD1094, decrypted) */
						/* 1989.01 Last Survivor (Japan) */
	DRIVER( smgpj )		/* 1989.06 Super Monaco GP (Japan, FD1094, decrypted) */
	DRIVER( smgpja )	/* 1989.06 Super Monaco GP (Japan, FD1094, decrypted) */
	DRIVER( smgp )		/* 1989.?? Super Monaco GP (World, FD1094, decrypted) */
	DRIVER( smgp6 )		/* 1989.?? Super Monaco GP (World, FD1094, decrypted) */
	DRIVER( smgp5 )		/* 1989.?? Super Monaco GP (World, FD1094, decrypted) */
	DRIVER( smgpu )		/* 1989.08 Super Monaco GP (US, FD1094, decrypted) */
	DRIVER( smgpu3 )	/* 1989.08 Super Monaco GP (US, FD1094, decrypted) */
	DRIVER( smgpu2 )	/* 1989.08 Super Monaco GP (US, FD1094, decrypted) */
	DRIVER( smgpu1 )	/* 1989.08 Super Monaco GP (US, FD1094, decrypted) */
	DRIVER( loffirej )	/* 1989.12 Line of Fire (Japan, FD1094, decrypted) */
	DRIVER( loffire )	/* 1989.?? Line of Fire (World, FD1094, decrypted) */
	DRIVER( loffireu )	/* 1990.04 Line of Fire (US, FD1094, decrypted) */
						/* 1990.03 Racing Hero (Japan) */
	DRIVER( rachero )	/* 1990.?? Racing Hero (World, FD1094, decrypted) */
	DRIVER( abcop )		/* 1990.?? A.B.Cop (World, FD1094, decrypted) */
						/* 1991.01 A.B.Cop (Japan) */
						/* 1990.10 GP Rider (Japan) */
	DRIVER( gprider )	/* 1990.?? GP Rider (World, protected) */
	DRIVER( gprider1 )	/* 1990.12 GP Rider (US, FD1094, decrypted) */

	/* Y-Board */
						/* 1988.05 Gaalxy Force (Japan) */
						/* 1988.08 Galaxy Force (US) */
	DRIVER( gforce2j )	/* 1988.07 Galaxy Force II (Japan) */
	DRIVER( gforce2 )	/* 1988.?? Galaxy Force II (World) */
						/* 1988.12 Galaxy Force II (US) */
						/* 1988.08 Power Drift (US) */
	DRIVER( pdriftj )	/* 1988.09 Power Drift (Japan) */
	DRIVER( pdrift )	/* 1988.?? Power Drift (World) */
	DRIVER( pdrifta )
	DRIVER( pdrifte )
	DRIVER( gloc )		/* 1990.04 G-LOC Air Battle (US) */
						/* 1990.05 G-LOC Air Battle (Japan) */
	DRIVER( glocr360 )	/* 1990.?? G-LOC (R360, World?) */
	DRIVER( strkfgtr )	/* 1991.06 Strike Fighter (Japan) */
	DRIVER( rchase )	/* 1991.09 Rail Chase (Japan) */
						/* 1991.09 Rail Chase (US) */

	/* Capcom CPS1 games */
	DRIVER( forgottn )	/*  7/1988 (c) 1988 (World) */
	DRIVER( forgottnu )	/*  7/1988 (c) 1988 (US) */
	DRIVER( lostwrld )	/*  7/1988 (c) 1988 (Japan) */
	DRIVER( lostwrldo )	/*  7/1988 (c) 1988 (Japan) */
	DRIVER( ghouls )	/* 12/1988 (c) 1988 (World) */
	DRIVER( ghoulsu )	/* 12/1988 (c) 1988 (US) */
	DRIVER( daimakai )	/* 12/1988 (c) 1988 (Japan) */
	DRIVER( daimakair )	/* 12/1988 (c) 1988 (Japan) */
	DRIVER( strider )	/*  3/1989 (c) 1989 (not explicitly stated but should be US) */
	DRIVER( striderua )	/*  3/1989 (c) 1989 (not explicitly stated but should be US) */
	DRIVER( striderj )	/*  3/1989 (c) 1989 */
	DRIVER( striderjr )	/*  3/1989 (c) 1989 */
	DRIVER( dynwar )	/*  4/1989 (c) 1989 (World) */
	DRIVER( dynwaru )	/*  4/1989 (c) 1989 (US) */
	DRIVER( dynwarj )	/*  4/1989 (c) 1989 (Japan) */
	DRIVER( willow )	/*  6/1989 (c) 1989 (US) */
	DRIVER( willowj )	/*  6/1989 (c) 1989 (Japan) */
	DRIVER( willowje )	/*  6/1989 (c) 1989 (Japan) */
	DRIVER( unsquad )	/*  8/1989 (c) 1989 */
	DRIVER( area88 )	/*  8/1989 (c) 1989 */
	DRIVER( ffight )	/* 12/1989 (c) (World) */
	DRIVER( ffightu )	/* 12/1989 (c) (US)    */
	DRIVER( ffightua )	/* 12/1989 (c) (US)    */
	DRIVER( ffightub )	/* 12/1989 (c) (US)    */
	DRIVER( ffightj )	/* 12/1989 (c) (Japan) */
	DRIVER( ffightj1 )	/* 12/1989 (c) (Japan) */
	DRIVER( ffightj2 )	/* 12/1989 (c) (Japan) */
	DRIVER( 1941 )		/*  2/1990 (c) 1990 (World) */
	DRIVER( 1941j )		/*  2/1990 (c) 1990 (Japan) */
	DRIVER( mercs )		/* 02/03/1990 (c) 1990 (World) */
	DRIVER( mercsu )	/* 02/03/1990 (c) 1990 (US)    */
	DRIVER( mercsua )	/* 08/06/1990 (c) 1990 (US)    */
	DRIVER( mercsj )	/* 02/03/1990 (c) 1990 (Japan) */
	DRIVER( mtwins )	/* 19/06/1990 (c) 1990 (World) */
	DRIVER( chikij )	/* 19/06/1990 (c) 1990 (Japan) */
	DRIVER( msword )	/* 25/07/1990 (c) 1990 (World) */
	DRIVER( mswordr1 )	/* 23/06/1990 (c) 1990 (World) */
	DRIVER( mswordu )	/* 25/07/1990 (c) 1990 (US)    */
	DRIVER( mswordj )	/* 23/06/1990 (c) 1990 (Japan) */
	DRIVER( cawing )	/* 12/10/1990 (c) 1990 (World) */
	DRIVER( cawingr1 )	/* 09/10/1990 (c) 1990 (World) */
	DRIVER( cawingu )	/* 12/10/1990 (c) 1990 (US) */
	DRIVER( cawingj )	/* 12/10/1990 (c) 1990 (Japan) */
	DRIVER( nemo )		/* 30/11/1990 (c) 1990 (World) */
	DRIVER( nemoj )		/* 20/11/1990 (c) 1990 (Japan) */
	DRIVER( sf2 )		/* 22/05/1991 (c) 1991 (World) */
	DRIVER( sf2eb )		/* 14/02/1991 (c) 1991 (World) */
	DRIVER( sf2ebbl )	/* 14/02/1991 (c) 1991 (World, bootleg) */
	DRIVER( sf2ua )		/* 06/02/1991 (c) 1991 (US)    */
	DRIVER( sf2ub )		/* 14/02/1991 (c) 1991 (US)    */
	DRIVER( sf2ud )		/* 18/03/1991 (c) 1991 (US)    */
	DRIVER( sf2ue )		/* 28/02/1991 (c) 1991 (US)    */
	DRIVER( sf2uf )		/* 11/04/1991 (c) 1991 (US)    */
	DRIVER( sf2ui )		/* 22/05/1991 (c) 1991 (US)    */
	DRIVER( sf2uk )		/* 01/11/1991 (c) 1991 (US)    */
	DRIVER( sf2j )		/* 10/12/1991 (c) 1991 (Japan) */
	DRIVER( sf2ja )		/* 14/02/1991 (c) 1991 (Japan) */
	DRIVER( sf2jc )		/* 06/03/1991 (c) 1991 (Japan) */
	DRIVER( sf2qp1 )	/* hack */
	DRIVER( 3wonders )	/* 20/05/1991 (c) 1991 (World) */
	DRIVER( 3wondersu )	/* 20/05/1991 (c) 1991 (US)    */
	DRIVER( wonder3 )	/* 20/05/1991 (c) 1991 (Japan) */
	DRIVER( 3wondersh )	/* hack? */
	DRIVER( kod )		/* 11/07/1991 (c) 1991 (World) */
	DRIVER( kodu )		/* 10/09/1991 (c) 1991 (US)    */
	DRIVER( kodj )		/* 05/08/1991 (c) 1991 (Japan) */
	DRIVER( kodb )		/* bootleg */
	DRIVER( captcomm )	/* 14/10/1991 (c) 1991 (World) */
	DRIVER( captcommu )	/* 28/ 9/1991 (c) 1991 (US)    */
	DRIVER( captcommj )	/* 02/12/1991 (c) 1991 (Japan) */
	DRIVER( captcommb )	/* bootleg */
	DRIVER( knights )	/* 27/11/1991 (c) 1991 (World) */
	DRIVER( knightsu )	/* 27/11/1991 (c) 1991 (US)    */
	DRIVER( knightsj )	/* 27/11/1991 (c) 1991 (Japan) */
	DRIVER( knightsb )	/* bootleg */
	DRIVER( sf2ce )		/* 13/03/1992 (c) 1992 (World) */
	DRIVER( sf2ceua )	/* 13/03/1992 (c) 1992 (US)    */
	DRIVER( sf2ceub )	/* 13/05/1992 (c) 1992 (US)    */
	DRIVER( sf2ceuc )	/* 03/08/1992 (c) 1992 (US)    */
	DRIVER( sf2cej )	/* 13/05/1992 (c) 1992 (Japan) */
	DRIVER( sf2rb )		/* hack */
	DRIVER( sf2rb2 )	/* hack */
	DRIVER( sf2rb3 )	/* hack */
	DRIVER( sf2red )	/* hack */
	DRIVER( sf2v004 )	/* hack */
	DRIVER( sf2acc )	/* hack */
	DRIVER( sf2accp2 )	/* hack */
	DRIVER( sf2dkot2 )	/* hack */
	DRIVER( sf2m1 )		/* hack */
	DRIVER( sf2m2 )		/* hack */
	DRIVER( sf2m3 )		/* hack */
	DRIVER( sf2m4 )		/* hack */
	DRIVER( sf2m5 )		/* hack */
	DRIVER( sf2m6 )		/* hack */
	DRIVER( sf2m7 )		/* hack */
	DRIVER( sf2yyc )	/* hack */
	DRIVER( sf2koryu )	/* hack */
	DRIVER( sf2mdt )	/* bootleg */
	DRIVER( varth )		/* 14/07/1992 (c) 1992 (World) */
	DRIVER( varthr1 )	/* 12/06/1992 (c) 1992 (World) */
	DRIVER( varthu )	/* 12/06/1992 (c) 1992 (US) */
	DRIVER( varthj )	/* 14/07/1992 (c) 1992 (Japan) */
	DRIVER( cworld2j )	/* 11/06/1992 (QUIZ 5) (c) 1992 (Japan) */
	DRIVER( wof )		/* 02/10/1992 (c) 1992 (World) (CPS1 + QSound) */
	DRIVER( wofa )		/* 05/10/1992 (c) 1992 (Asia)  (CPS1 + QSound) */
	DRIVER( wofu )		/* 31/10/1992 (c) 1992 (US) (CPS1 + QSound) */
	DRIVER( wofj )		/* 31/10/1992 (c) 1992 (Japan) (CPS1 + QSound) */
	DRIVER( wofhfh )	/* bootleg */
	DRIVER( sf2hf )		/* 09/12/1992 (c) 1992 (World) */
	DRIVER( sf2t )		/* 09/12/1992 (c) 1992 (US)    */
	DRIVER( sf2tj )		/* 09/12/1992 (c) 1992 (Japan) */
	DRIVER( dino )		/* 01/02/1993 (c) 1993 (World) (CPS1 + QSound) */
	DRIVER( dinou )		/* 01/02/1993 (c) 1993 (US)    (CPS1 + QSound) */
	DRIVER( dinoj )		/* 01/02/1993 (c) 1993 (Japan) (CPS1 + QSound) */
	DRIVER( dinopic )	/* bootleg */
	DRIVER( dinopic2 )	/* bootleg */
	DRIVER( punisher )	/* 22/04/1993 (c) 1993 (World) (CPS1 + QSound) */
	DRIVER( punisheru )	/* 22/04/1993 (c) 1993 (US)    (CPS1 + QSound) */
	DRIVER( punisherj )	/* 22/04/1993 (c) 1993 (Japan) (CPS1 + QSound) */
	DRIVER( punipic )	/* bootleg */
	DRIVER( punipic2 )	/* bootleg */
	DRIVER( punipic3 )	/* bootleg */
	DRIVER( slammast )	/* 13/07/1993 (c) 1993 (World) (CPS1 + QSound) */
	DRIVER( slammastu )	/* 13/07/1993 (c) 1993 (US)    (CPS1 + QSound) */
	DRIVER( mbomberj )	/* 13/07/1993 (c) 1993 (Japan) (CPS1 + QSound) */
	DRIVER( mbombrd )	/* 06/12/1993 (c) 1993 (World) (CPS1 + QSound) */
	DRIVER( mbombrdj )	/* 06/12/1993 (c) 1993 (Japan) (CPS1 + QSound) */
	DRIVER( pnickj )	/* 08/06/1994 (c) 1994 Compile + Capcom license (Japan) not listed on Capcom's site */
	DRIVER( qad )		/* 01/07/1992 (c) 1992 (US)    */
	DRIVER( qadj )		/* 21/09/1994 (c) 1994 (Japan) */
	DRIVER( qtono2 )	/* 23/01/1995 (c) 1995 (Japan) */
	DRIVER( pang3 )		/* 11/05/1995 (c) 1995 Mitchell (Euro) not listed on Capcom's site */
	DRIVER( pang3j )	/* 11/05/1995 (c) 1995 Mitchell (Japan) not listed on Capcom's site */
	DRIVER( megaman )	/* 06/10/1995 (c) 1995 (Asia)  */
	DRIVER( rockmanj )	/* 22/09/1995 (c) 1995 (Japan) */

	DRIVER( fcrash )	/* bootleg of Final Fight */

	/* Capcom CPS2 games */
	/* list completed by CPS2Shock */
	/* http://cps2shock.retrogames.com */
	DRIVER( ssf2 )		/* 11/09/1993 (c) 1993 (World) */
	DRIVER( ssf2u )		/* 11/09/1993 (c) 1993 (US) */
	DRIVER( ssf2a )		/* 05/10/1993 (c) 1993 (Asia) */
	DRIVER( ssf2ar1 )	/* 14/09/1993 (c) 1993 (Asia) */
	DRIVER( ssf2j )		/* 05/10/1993 (c) 1993 (Japan) */
	DRIVER( ssf2jr1 )	/* 11/09/1993 (c) 1993 (Japan) */
	DRIVER( ssf2jr2 )	/* 10/09/1993 (c) 1993 (Japan) */
	DRIVER( ssf2tb )	/* 11/19/1993 (c) 1993 (World) */
	DRIVER( ssf2tbr1 )	/* 11/09/1993 (c) 1993 (World) */
	DRIVER( ssf2tbj )	/* 11/09/1993 (c) 1993 (Japan) */
	DRIVER( ecofghtr )	/* 03/12/1993 (c) 1993 (World) */
	DRIVER( ecofghtru )	/* 15/02/1994 (c) 1993 (US) */
	DRIVER( ecofghtru1 )/* 03/12/1993 (c) 1993 (US) */
	DRIVER( ecofghtra )	/* 03/12/1993 (c) 1993 (Asia) */
	DRIVER( uecology ) 	/* 03/12/1993 (c) 1993 (Japan) */
	DRIVER( ddtod )		/* 12/04/1994 (c) 1993 (Euro) */
	DRIVER( ddtodr1 )	/* 13/01/1994 (c) 1993 (Euro) */
	DRIVER( ddtodu )	/* 25/01/1994 (c) 1993 (US) */
	DRIVER( ddtodur1 )	/* 13/01/1994 (c) 1993 (US) */
	DRIVER( ddtodj )	/* 12/04/1994 (c) 1993 (Japan) */
	DRIVER( ddtodjr1 )	/* 25/01/1994 (c) 1993 (Japan) */
	DRIVER( ddtodjr2 )	/* 13/01/1994 (c) 1993 (Japan) */
	DRIVER( ddtoda )	/* 13/01/1994 (c) 1993 (Asia) */
	DRIVER( ddtodh )	/* 12/04/1994 (c) 1993 (Hispanic) */
	DRIVER( ddtodhr1 )	/* 25/01/1994 (c) 1993 (Hispanic) */
	DRIVER( ssf2t )		/* 23/02/1994 (c) 1994 (World) */
	DRIVER( ssf2tu )	/* 23/03/1994 (c) 1994 (US) */
	DRIVER( ssf2tur1 )	/* 23/02/1994 (c) 1994 (US) */
	DRIVER( ssf2ta )	/* 23/02/1994 (c) 1994 (Asia) */
	DRIVER( ssf2xj )	/* 23/02/1994 (c) 1994 (Japan) */
	DRIVER( avsp )		/* 20/05/1994 (c) 1994 (Euro) */
	DRIVER( avspu )		/* 20/05/1994 (c) 1994 (US) */
	DRIVER( avspj )		/* 20/05/1994 (c) 1994 (Japan) */
	DRIVER( avspa )		/* 20/05/1994 (c) 1994 (Asia) */
	DRIVER( avsph )		/* 20/05/1994 (c) 1994 (Hispanic) */
						/*    06/1994? Galum Pa! (not listed on Capcom's site) */
	DRIVER( dstlk )		/* 05/07/1994 (c) 1994 (Euro) */
	DRIVER( dstlku )	/* 18/08/1994 (c) 1994 (US) */
	DRIVER( dstlkur1 )	/* 05/07/1994 (c) 1994 (US) */
	DRIVER( dstlka )	/* 05/07/1994 (c) 1994 (Asia) */
	DRIVER( vampj )		/* 05/07/1994 (c) 1994 (Japan) */
	DRIVER( vampja )	/* 05/07/1994 (c) 1994 (Japan) */
	DRIVER( vampjr1 )	/* 30/06/1994 (c) 1994 (Japan) */
	DRIVER( ringdest )	/* 02/09/1994 (c) 1994 (Euro) */
	DRIVER( smbomb )	/* 31/08/1994 (c) 1994 (Japan) */
	DRIVER( smbombr1 )	/* 08/08/1994 (c) 1994 (Japan) */
	DRIVER( armwar )	/* 24/10/1994 (c) 1994 (Euro) */
	DRIVER( armwarr1 )	/* 11/10/1994 (c) 1994 (Euro) */
	DRIVER( armwaru )	/* 24/10/1994 (c) 1994 (US) */
	DRIVER( armwaru1 )	/* 20/09/1994 (c) 1994 (US) */
	DRIVER( pgear )		/* 24/10/1994 (c) 1994 (Japan) */
	DRIVER( pgearr1 )	/* 16/09/1994 (c) 1994 (Japan) */
	DRIVER( armwara )	/* 20/09/1994 (c) 1994 (Asia) */
	DRIVER( xmcota )	/* 05/01/1995 (c) 1994 (Euro) */
	DRIVER( xmcotau )	/* 05/01/1995 (c) 1994 (US) */
	DRIVER( xmcotah )	/* 31/03/1995 (c) 1994 (Hispanic) */
	DRIVER( xmcotaj )	/* 22/12/1994 (c) 1994 (Japan) */
	DRIVER( xmcotaj1 )	/* 19/12/1994 (c) 1994 (Japan) */
	DRIVER( xmcotaj2 )	/* 17/12/1994 (c) 1994 (Japan) */
	DRIVER( xmcotaa )	/* 17/12/1994 (c) 1994 (Asia) */
	DRIVER( xmcotajr )	/* 08/12/1994 (c) 1994 (Japan Rent) */
	DRIVER( nwarr )		/* 16/03/1995 (c) 1995 (Euro) */
	DRIVER( nwarru )	/* 06/04/1995 (c) 1995 (US) */
	DRIVER( nwarrh )	/* 03/04/1995 (c) 1995 (Hispanic) */
	DRIVER( nwarrb )	/* 03/04/1995 (c) 1995 (Brazil) */
	DRIVER( nwarra )	/* 02/03/1995 (c) 1995 (Asia) */
	DRIVER( vhuntj )	/* 02/03/1995 (c) 1995 (Japan) */
	DRIVER( vhuntjr1 )	/* 07/03/1995 (c) 1995 (Japan) */
	DRIVER( vhuntjr2 )	/* 02/03/1995 (c) 1995 (Japan) */
	DRIVER( cybots )	/* 24/04/1995 (c) 1995 (Euro) */
	DRIVER( cybotsu )	/* 24/04/1995 (c) 1995 (US) */
	DRIVER( cybotsj )	/* 20/04/1995 (c) 1995 (Japan) */
	DRIVER( sfa )		/* 27/07/1995 (c) 1995 (Euro) */
	DRIVER( sfar1 )		/* 18/07/1995 (c) 1995 (Euro) */
	DRIVER( sfar2 )		/* 27/06/1995 (c) 1995 (Euro) */
	DRIVER( sfar3 )		/* 05/06/1995 (c) 1995 (Euro) */
	DRIVER( sfau )		/* 27/06/1995 (c) 1995 (US) */
	DRIVER( sfza )		/* 27/06/1995 (c) 1995 (Asia) */
	DRIVER( sfzj )		/* 27/07/1995 (c) 1995 (Japan) */
	DRIVER( sfzjr1 )	/* 27/06/1995 (c) 1995 (Japan) */
	DRIVER( sfzjr2 )	/* 05/06/1995 (c) 1995 (Japan) */
	DRIVER( sfzh )		/* 27/06/1995 (c) 1995 (Hispanic) */
	DRIVER( sfzb )		/* 09/11/1995 (c) 1995 (Brazil) */
	DRIVER( sfzbr1 )	/* 27/07/1995 (c) 1995 (Brazil) */
	DRIVER( mmancp2u )	/* 06/10/1995 (c) 1995 (Japan) */
	DRIVER( rmancp2j )	/* 22/09/1995 (c) 1995 (Japan) */
	DRIVER( msh )		/* 24/10/1995 (c) 1995 (Euro) */
	DRIVER( mshu )		/* 24/10/1995 (c) 1995 (US) */
	DRIVER( mshj )		/* 17/11/1995 (c) 1995 (Japan) */
	DRIVER( mshjr1 )	/* 24/10/1995 (c) 1995 (Japan) */
	DRIVER( msha )		/* 24/10/1995 (c) 1995 (Asia) */
	DRIVER( mshh )		/* 17/11/1995 (c) 1996 (Hispanic) */
	DRIVER( mshb )		/* 17/11/1995 (c) 1996 (Brazil) */
	DRIVER( 19xx )		/* 07/12/1995 (c) 1996 (US) */
	DRIVER( 19xxj )		/* 25/12/1995 (c) 1996 (Japan) */
	DRIVER( 19xxjr1 )	/* 07/12/1995 (c) 1996 (Japan) */
	DRIVER( 19xxa )		/* 07/12/1995 (c) 1996 (Asia) */
	DRIVER( 19xxh )		/* 18/12/1995 (c) 1996 (Hispanic) */
	DRIVER( 19xxb )		/* 18/12/1995 (c) 1996 (Brazil) */
	DRIVER( ddsom )		/* 19/06/1996 (c) 1996 (Euro) */
	DRIVER( ddsomr1 )	/* 23/02/1996 (c) 1996 (Euro) */
	DRIVER( ddsomr2 )	/* 09/02/1996 (c) 1996 (Euro) */
	DRIVER( ddsomr3 )	/* 08/02/1996 (c) 1996 (Euro) */
	DRIVER( ddsomu )	/* 19/06/1996 (c) 1996 (US) */
	DRIVER( ddsomur1 )	/* 09/02/1996 (c) 1996 (US) */
	DRIVER( ddsomjr1 )	/* 06/02/1996 (c) 1996 (Japan) */
	DRIVER( ddsomj )	/* 19/06/1996 (c) 1996 (Japan) */
	DRIVER( ddsoma )	/* 19/06/1996 (c) 1996 (Asia) */
	DRIVER( ddsomb )	/* 23/02/1996 (c) 1996 (Brazil) */
	DRIVER( sfa2 )		/* 06/03/1996 (c) 1996 (Euro) */
	DRIVER( sfa2u )		/* 06/03/1996 (c) 1996 (US) */
	DRIVER( sfz2j )		/* 27/02/1996 (c) 1996 (Japan) */
	DRIVER( sfz2a )		/* 27/02/1996 (c) 1996 (Asia) */
	DRIVER( sfz2b )		/* 31/05/1996 (c) 1996 (Brazil) */
	DRIVER( sfz2br1 )	/* 04/03/1996 (c) 1996 (Brazil) */
	DRIVER( sfz2h )		/* 04/03/1996 (c) 1996 (Hispanic) */
	DRIVER( sfz2n )		/* 29/02/1996 (c) 1996 (Oceania) */
	DRIVER( spf2t )		/* 20/06/1996 (c) 1996 (US) */
	DRIVER( spf2xj )	/* 31/05/1996 (c) 1996 (Japan) */
	DRIVER( spf2ta )	/* 29/05/1996 (c) 1996 (Asia) */
	DRIVER( qndream )	/* 26/06/1996 (c) 1996 (Japan) */
	DRIVER( megaman2 )	/* 08/07/1996 (c) 1996 (US) */
	DRIVER( megaman2a )	/* 08/07/1996 (c) 1996 (Asia) */
	DRIVER( rckman2j )	/* 08/07/1996 (c) 1996 (Japan) */
	DRIVER( gigamn2 )	/* bootleg */
	DRIVER( sfz2al )	/* 26/08/1996 (c) 1996 (Asia) */
	DRIVER( sfz2alj )	/* 05/08/1996 (c) 1996 (Japan) */
	DRIVER( sfz2alh )	/* 13/08/1996 (c) 1996 (Hispanic) */
	DRIVER( sfz2alb )	/* 13/08/1996 (c) 1996 (Brazil) */
	DRIVER( xmvsf )		/* 04/10/1996 (c) 1996 (Euro) */
	DRIVER( xmvsfr1 )	/* 10/09/1996 (c) 1996 (Euro) */
	DRIVER( xmvsfu )	/* 23/10/1996 (c) 1996 (US) */
	DRIVER( xmvsfur1 )	/* 04/10/1996 (c) 1996 (US) */
	DRIVER( xmvsfj )	/* 04/10/1996 (c) 1996 (Japan) */
	DRIVER( xmvsfjr1 )	/* 10/09/1996 (c) 1996 (Japan) */
	DRIVER( xmvsfjr2 )	/* 09/09/1996 (c) 1996 (Japan) */
	DRIVER( xmvsfa )	/* 23/10/1996 (c) 1996 (Asia) */
	DRIVER( xmvsfar1 )	/* 19/09/1996 (c) 1996 (Asia) */
	DRIVER( xmvsfh )	/* 04/10/1996 (c) 1996 (Hispanic) */
	DRIVER( xmvsfb )	/* 23/10/1996 (c) 1996 (Brazil) */
	DRIVER( batcir )	/* 19/03/1997 (c) 1997 (Euro) */
	DRIVER( batcirj )	/* 19/03/1997 (c) 1997 (Japan) */
	DRIVER( batcira )	/* 19/03/1997 (c) 1997 (Asia) */
	DRIVER( vsav )		/* 19/05/1997 (c) 1997 (Euro) */
	DRIVER( vsavu )		/* 19/05/1997 (c) 1997 (US) */
	DRIVER( vsavj )		/* 19/05/1997 (c) 1997 (Japan) */
	DRIVER( vsava )		/* 19/05/1997 (c) 1997 (Asia) */
	DRIVER( vsavh )		/* 19/05/1997 (c) 1997 (Hispanic) */
	DRIVER( mshvsf )	/* 25/06/1997 (c) 1997 (Euro) */
	DRIVER( mshvsfu )	/* 27/08/1997 (c) 1997 (US) */
	DRIVER( mshvsfu1 )	/* 25/06/1997 (c) 1997 (US) */
	DRIVER( mshvsfj )	/* 07/07/1997 (c) 1997 (Japan) */
	DRIVER( mshvsfj1 )	/* 02/07/1997 (c) 1997 (Japan) */
	DRIVER( mshvsfj2 )	/* 25/06/1997 (c) 1997 (Japan) */
	DRIVER( mshvsfh )	/* 25/06/1997 (c) 1997 (Hispanic) */
	DRIVER( mshvsfa )	/* 25/06/1997 (c) 1997 (Asia) */
	DRIVER( mshvsfa1 )	/* 20/06/1997 (c) 1997 (Asia) */
	DRIVER( mshvsfb )	/* 27/08/1997 (c) 1997 (Brazil) */
	DRIVER( mshvsfb1 )	/* 25/06/1997 (c) 1997 (Brazil) */
	DRIVER( csclub )	/* 17/10/1997 (c) 1997 (Euro) */
	DRIVER( csclub1 )	/* 22/07/1997 (c) 1997 (Euro) */
	DRIVER( csclubj )	/* 22/07/1997 (c) 1997 (Japan) */
	DRIVER( cscluba )	/* 22/07/1997 (c) 1997 (Asia) */
	DRIVER( csclubh )	/* 22/07/1997 (c) 1997 (Hispanic) */
	DRIVER( sgemf )		/* 04/09/1997 (c) 1997 (US) */
	DRIVER( pfghtj )	/* 04/09/1997 (c) 1997 (Japan) */
	DRIVER( sgemfa )	/* 04/09/1997 (c) 1997 (Asia) */
	DRIVER( sgemfh )	/* 04/09/1997 (c) 1997 (Hispanic) */
	DRIVER( vhunt2r1 )	/* 13/09/1997 (c) 1997 (Japan) */
	DRIVER( vhunt2 )	/* 29/09/1997 (c) 1997 (Japan) */
	DRIVER( vsav2 )		/* 13/09/1997 (c) 1997 (Japan) */
	DRIVER( mvsc )		/* 23/01/1998 (c) 1998 (Euro) */
	DRIVER( mvscr1 )	/* 12/01/1998 (c) 1998 (Euro) */
	DRIVER( mvscu )		/* 23/01/1998 (c) 1998 (US) */
	DRIVER( mvscj )		/* 23/01/1998 (c) 1998 (Japan) */
	DRIVER( mvscjr1 )	/* 12/01/1998 (c) 1998 (Japan) */
	DRIVER( mvsca )		/* 23/01/1998 (c) 1998 (Asia) */
	DRIVER( mvscar1 )	/* 12/01/1998 (c) 1998 (Asia) */
	DRIVER( mvsch )		/* 23/01/1998 (c) 1998 (Hispanic) */
	DRIVER( mvscb )		/* 23/01/1998 (c) 1998 (Brazil) */
	DRIVER( sfa3 )		/* 04/09/1998 (c) 1998 (US) */
	DRIVER( sfa3u )		/* 04/09/1998 (c) 1998 (US) */
	DRIVER( sfa3ur1 )	/* 29/06/1998 (c) 1998 (US) */
	DRIVER( sfa3b )		/* 29/06/1998 (c) 1998 (Brazil) */
	DRIVER( sfz3j )		/* 04/09/1998 (c) 1998 (Japan) */
	DRIVER( sfz3jr1 )	/* 27/07/1998 (c) 1998 (Japan) */
	DRIVER( sfz3jr2 )	/* 29/06/1998 (c) 1998 (Japan) */
	DRIVER( sfz3a )		/* 04/09/1998 (c) 1998 (Asia) */
	DRIVER( sfz3ar1 )	/* 01/07/1998 (c) 1998 (Asia) */
	DRIVER( gigawing )	/* 22/02/1999 (c) 1999 Takumi (US) */
	DRIVER( gigawingj )	/* 23/02/1999 (c) 1999 Takumi (Japan) */
	DRIVER( gigawinga )	/* 22/02/1999 (c) 1999 Takumi (Asia) */
	DRIVER( gigawingb )	/* 22/02/1999 (c) 1999 Takumi (Brazil) */
	DRIVER( jyangoku )	/* 27/05/1999 (c) 1999 (Japan) */
	DRIVER( dimahoo )	/* 21/01/2000 (c) 2000 Eighting/Raizing (US) */
	DRIVER( dimahoou )	/* 21/01/2000 (c) 2000 Eighting/Raizing (US) */
	DRIVER( gmahou )	/* 21/01/2000 (c) 2000 Eighting/Raizing (Japan) */
	DRIVER( mmatrix )	/* 12/04/2000 (c) 2000 Takumi (US) */
	DRIVER( mmatrixj )	/* 12/04/2000 (c) 2000 Takumi (Japan) */
	DRIVER( 1944 )		/* 20/06/2000 (c) 2000 Eighting/Raizing (US) */
	DRIVER( 1944j )		/* 20/06/2000 (c) 2000 Eighting/Raizing (Japan) */
	DRIVER( mpang )		/* 10/10/2000 (c) 2000 Mitchell (Euro) */
	DRIVER( mpangr1 )	/* 25/09/2000 (c) 2000 Mitchell (Euro) */
	DRIVER( mpangu )	/* 10/10/2000 (c) 2000 Mitchell (US) */
	DRIVER( mpangj )	/* 11/10/2000 (c) 2000 Mitchell (Japan) */
	DRIVER( progear )	/* 17/01/2001 (c) 2001 Cave (US) */
	DRIVER( progearj )	/* 17/01/2001 (c) 2001 Cave (Japan) */
	DRIVER( progeara )	/* 17/01/2001 (c) 2001 Cave (Asia) */
	DRIVER( pzloop2 )	/* 02/03/2001 (c) 2001 Mitchell (Euro) */
	DRIVER( pzloop2j )	/* 05/02/2001 (c) 2001 Mitchell (Japan) */
	DRIVER( choko )		/* 20/08/2001 (c) 2001 Mitchell (Japan) */
	DRIVER( hsf2j )		/* 22/12/2003 (c) 2003 Hyper Street Fighter 2 (Japan) */
	DRIVER( hsf2 )		/* 02/02/2004 (c) 2004 Hyper Street Fighter 2 (Asia) */

	/* CPS2 'Phoenix' bootlegs */
	DRIVER( ssf2ud )
	DRIVER( ddtodd )
	DRIVER( avspd )
	DRIVER( dstlku1d )
	DRIVER( ringdstd )
	DRIVER( xmcotad )
	DRIVER( nwarrud )
	DRIVER( sfad )
	DRIVER( mshud )
	DRIVER( 19xxd )
	DRIVER( sfz2ad )
	DRIVER( spf2xjd )
	DRIVER( ddsomud )
	DRIVER( megamn2d )
	DRIVER( sfz2ald )
	DRIVER( xmvsfu1d )
	DRIVER( batcird )
	DRIVER( vsavd )
	DRIVER( mvscud )
	DRIVER( sfa3ud )
	DRIVER( gwingjd )
	DRIVER( 1944d )
	DRIVER( progerjd )
	DRIVER( hsf2d )
	DRIVER( ssf2tbd )
	DRIVER( ssf2xjd )
	DRIVER( sgemfd )
	DRIVER( armwar1d )
	DRIVER( dimahoud )
	DRIVER( mmatrixd )

	/* Midway 8080 b/w games */
	DRIVER( seawolf )	/* 596 [1976] */
	DRIVER( gunfight )	/* 597 [1975] */
						/* 603 - Top Gun [1976] */
	DRIVER( tornbase )	/* 605 [1976] */
	DRIVER( 280zzzap )	/* 610 [1976] */
	DRIVER( maze )		/* 611 [1976] */
	DRIVER( boothill )	/* 612 [1977] */
	DRIVER( checkmat )	/* 615 [1977] */
	DRIVER( desertgu )	/* 618 [1977] */
	DRIVER( roadrunm )	/* 618 [1977] */
	DRIVER( dplay )		/* 619 [1977] */
	DRIVER( lagunar )	/* 622 [1977] */
	DRIVER( gmissile )	/* 623 [1977] */
	DRIVER( m4 )		/* 626 [1977] */
	DRIVER( clowns )	/* 630 [1978] */
	DRIVER( clowns1 )	/* 630 [1978] */
	DRIVER( spacwalk )	/* 640 [1978] */
	DRIVER( einning )	/* 642 [1978] Midway */
	DRIVER( shuffle )	/* 643 [1978] */
	DRIVER( dogpatch )	/* 644 [1977] */
	DRIVER( spcenctr )	/* 645 (c) 1980 Midway */
	DRIVER( phantom2 )	/* 652 [1979] */
	DRIVER( bowler )	/* 730 [1978] Midway */
	DRIVER( invaders )	/* 739 [1979] */
	DRIVER( blueshrk )	/* 742 [1978] */
	DRIVER( invad2ct )	/* 851 (c) 1980 Midway */
	DRIVER( invadpt2 )	/* 852 [1980] Taito */
	DRIVER( invaddlx )	/* 852 [1980] Midway */
	DRIVER( moonbase )	/* Zeta - Nichibutsu */
						/* 870 - Space Invaders Deluxe cocktail */
	DRIVER( searthin )	/* bootleg */
	DRIVER( searthina )	/* bootleg */
	DRIVER( invadrmr )	/* (c) 1978 Model Racing */
	DRIVER( spaceatt )	/* (c) 1978 Video Games GMBH */
	DRIVER( spaceat2 )	/* (c) 1980 Zenitone-Microsec Ltd */
	DRIVER( sinvzen )	/* Zenitone-Microsec Ltd */
	DRIVER( superinv )	/* bootleg */
	DRIVER( invasion )	/* Sidam */
	DRIVER( sstrangr )	/* (c) 1978 Yachiyo Electronics, Ltd. */
	DRIVER( sstrangr2 )	/* (c) 1979 Yachiyo Electronics, Ltd. */
	DRIVER( sinvemag )	/* Zenitone-Microsec Ltd. */
	DRIVER( jspecter )	/* (c) 1979 Jatre */
	DRIVER( jspecter2 )	/* (c) 1979 Jatre */
	DRIVER( invrvnge )	/* Zenitone-Microsec Ltd. */
	DRIVER( invrvngea )	/* Zenitone-Microsec Ltd. (Dutchford license) */
	DRIVER( galxwars )	/* (c) 1979 Universal */
	DRIVER( galxwars2 )	/* (c) 1979 Universal */
	DRIVER( galxwarst )	/* (c) 1979 Taito? */
	DRIVER( starw )		/* bootleg */
	DRIVER( lrescue )	/* LR  (c) 1979 Taito */
	DRIVER( mlander )	/* (c) 1980 Leisure Time Electronics */
	DRIVER( lrescuem )	/* Model Racing bootleg */
	DRIVER( grescue )	/* bootleg? */
	DRIVER( desterth )	/* bootleg */
	DRIVER( cosmicmo )	/* Universal */
	DRIVER( cosmicm2 )	/* Universal */
	DRIVER( rollingc )	/* Nichibutsu */
	DRIVER( ozmawars )	/* Shin Nihon Kikaku (SNK) */
	DRIVER( ozmawars2 )	/* Shin Nihon Kikaku (SNK) */
	DRIVER( solfight )	/* bootleg */
	DRIVER( spaceph )	/* Zilec Games */
	DRIVER( schaser )	/* RT  Taito */
	DRIVER( schasercv )	/* RT  Taito */
	DRIVER( lupin3 )	/* LP  (c) 1980 Taito */
	DRIVER( lupin3a )	/* LP  (c) 1980 Taito */
	DRIVER( intruder )	/* (c) 1980 GamePlan (Taito) */
	DRIVER( spclaser )	/* (c) 1980 GamePlan (Taito) */
	DRIVER( laser )		/* (c) 1980 Leisure Time Electronics Inc. */
	DRIVER( spcewarl )	/* (c) 1979 Leijac Corporation (Konami) */
	DRIVER( polaris )	/* PS  (c) 1980 Taito */
	DRIVER( polarisa )	/* PS  (c) 1980 Taito */
	DRIVER( ballbomb )	/* TN  (c) 1980 Taito */
	DRIVER( indianbt )	/* (c) 1980 Taito */
	DRIVER( steelwkr )	/* (c) 1980 Taito */
	DRIVER( m79amb )	/* (c) 1977 RamTek */
	DRIVER( alieninv )	/* bootleg */
	DRIVER( tst_invd )	/* Test ROM */
	DRIVER( sitv )		/* (c) 1979 Taito */
	DRIVER( sicv )		/* (c) 1979 Taito */
	DRIVER( sisv )		/* (c) 1978 Taito */
	DRIVER( sisv2 )		/* (c) 1978 Taito */
	DRIVER( spacewr3 )	/* bootleg */
	DRIVER( invaderl )	/* bootleg */
	DRIVER( invader4 )	/* bootleg */
	DRIVER( yosakdon )	/* (c) 1979 Yosaku To Donbei */
	DRIVER( yosakdona )	/* (c) 1979 Yosaku To Donbei */
	DRIVER( spceking )	/* (c) 1978 Leijac Corporation (Konami) */
	DRIVER( spcewars )	/* (c) 1978 Sanritsu */
	DRIVER( astropal )	/* (c) 19?? Sidam */
	DRIVER( cosmo )		/* TDS+Mints */
	DRIVER( darthvdr )	/* bootleg */

	DRIVER( sspeedr )	/* 1979 Midway */

	/* Similar but with a M6800 instead of an 8080 */
	DRIVER( sflush )	/* (c)1979 Taito */

	/* Meadows S2650 games */
	DRIVER( lazercmd )	/* [1976?] */
	DRIVER( bbonk )		/* [1976?] */
	DRIVER( deadeye )	/* [1978?] */
	DRIVER( bowl3d )	/* [1978?] */
	DRIVER( gypsyjug )	/* [1978?] */
	DRIVER( minferno )	/* [1978?] */
	DRIVER( medlanes )	/* [1977?] */

	/* CVS games */
	DRIVER( cosmos )	/* (c) 1981 Century */
	DRIVER( darkwar )	/* (c) 1981 Century */
	DRIVER( spacefrt )	/* (c) 1981 Century */
	DRIVER( 8ball )		/* (c) 1982 Century */
	DRIVER( 8ball1 )	/* (c) 1982 Century */
	DRIVER( logger )	/* (c) 1982 Century */
	DRIVER( dazzler )	/* (c) 1982 Century */
	DRIVER( diggerc )	/* (c) 1982 Century */
	DRIVER( wallst )	/* (c) 1982 Century */
	DRIVER( radarzon )	/* (c) 1982 Century */
	DRIVER( radarzon1 )	/* (c) 1982 Century */
	DRIVER( radarzont )	/* (c) 1982 Tuni Electro Service */
	DRIVER( outline )	/* (c) 1982 Century */
	DRIVER( goldbug )	/* (c) 1982 Century */
	DRIVER( heartatk )	/* (c) 1983 Century Electronics */
	DRIVER( hunchbak )	/* (c) 1983 Century */
	DRIVER( hunchbaka )	/* (c) 1983 Century */
	DRIVER( superbik )	/* (c) 1983 Century */
	DRIVER( raiders )	/* (c) 1983 Century Electronics UK */
	DRIVER( hero )		/* (c) 1983 Seatongrove (c) 1984 CVS */
	DRIVER( huncholy )	/* (c) 1984 Seatongrove (c) CVS */

	/* Zaccaria Hardware (similar to CVS) */
	DRIVER( quasar )	/* (c) 1980 Zelco Games Italy */
	DRIVER( quasara )	/* (c) 1980 Zelco Games Italy */

	/* Midway "Astrocade" games */
	DRIVER( seawolf2 )	/* (c) 1978 */
	DRIVER( spacezap )	/* (c) 1980 */
	DRIVER( ebases )	/* (c) 1980 */
	DRIVER( wow )		/* (c) 1980 */
	DRIVER( gorf )		/* (c) 1981 */
	DRIVER( gorfpgm1 )	/* (c) 1981 */
	DRIVER( robby )		/* (c) 1981 Bally Midway */
	DRIVER( demndrgn )	/* (c) 1982 Bally Midway */
	DRIVER( profpac )	/* (c) 1983 Bally Midway */
	DRIVER( tenpindx )	/* (c) 1983 Bally Midway */

	/* Bally Midway MCR games */
	/* MCR1 */
	DRIVER( solarfox )	/* (c) 1981 */
	DRIVER( kick )		/* (c) 1981 */
	DRIVER( kickman )	/* (c) 1981 */
	DRIVER( kickc )		/* (c) 1981 */
	/* MCR2 */
	DRIVER( shollow )	/* (c) 1981 */
	DRIVER( shollow2 )	/* (c) 1981 */
	DRIVER( tron )		/* (c) 1982 */
	DRIVER( tron2 )		/* (c) 1982 */
	DRIVER( tron3 )		/* (c) 1982 */
	DRIVER( tron4 )		/* (c) 1982 */
	DRIVER( kroozr )	/* (c) 1982 */
	DRIVER( domino )	/* (c) 1982 */
	DRIVER( wacko )		/* (c) 1982 */
	DRIVER( twotiger )	/* (c) 1984 */
	DRIVER( twotigerc )	/* (c) 1984 */
	/* MCR2 + MCR3 sprites */
	DRIVER( journey )	/* (c) 1983 */
	/* MCR3 */
	DRIVER( tapper )	/* (c) 1983 */
	DRIVER( tappera )	/* (c) 1983 */
	DRIVER( sutapper )	/* (c) 1983 */
	DRIVER( rbtapper )	/* (c) 1984 */
	DRIVER( timber )	/* (c) 1984 */
	DRIVER( dotron )	/* (c) 1983 */
	DRIVER( dotrona )	/* (c) 1983 */
	DRIVER( dotrone )	/* (c) 1983 */
	DRIVER( nflfoot )	/* (c) 1983 + laserdisk */
	DRIVER( demoderb )	/* (c) 1984 */
	DRIVER( demoderm )	/* (c) 1984 */
	DRIVER( sarge )		/* (c) 1985 */
	DRIVER( rampage )	/* (c) 1986 */
	DRIVER( rampage2 )	/* (c) 1986 */
	DRIVER( powerdrv )	/* (c) 1986 */
	DRIVER( stargrds )	/* (c) 1987 */
	DRIVER( maxrpm )	/* (c) 1986 */
	DRIVER( spyhunt )	/* (c) 1983 */
	DRIVER( spyhuntp )	/* (c) 1983 */
	DRIVER( turbotag )	/* (c) 1985 */
	DRIVER( crater )	/* (c) 1984 */
	/* MCR 68000 */
	DRIVER( zwackery )	/* (c) 1984 */
	DRIVER( xenophob )	/* (c) 1987 */
	DRIVER( spyhunt2 )	/* (c) 1987 */
	DRIVER( spyhunt2a )	/* (c) 1987 */
	DRIVER( blasted )	/* (c) 1988 */
	DRIVER( archrivl )	/* (c) 1989 */
	DRIVER( archrivl2 )	/* (c) 1989 */
	DRIVER( trisport )	/* (c) 1989 */
	DRIVER( pigskin )	/* (c) 1990 */

	/* Taito "Qix hardware" games */
	DRIVER( qix )		/* LK  (c) 1981 Taito America Corporation */
	DRIVER( qixa )		/* LK  (c) 1981 Taito America Corporation */
	DRIVER( qixb )		/* LK  (c) 1981 Taito America Corporation */
	DRIVER( qixo )		/* LK  (c) 1981 Taito America Corporation */
	DRIVER( qix2 )		/* ??  (c) 1981 Taito America Corporation */
	DRIVER( sdungeon )	/* SD  (c) 1981 Taito America Corporation */
	DRIVER( elecyoyo )	/* YY  (c) 1982 Taito America Corporation */
	DRIVER( elecyoyo2 )	/* YY  (c) 1982 Taito America Corporation */
	DRIVER( kram )		/* KS  (c) 1982 Taito America Corporation */
	DRIVER( kram2 )		/* KS  (c) 1982 Taito America Corporation */
	DRIVER( kram3 )		/* KS  (c) 1982 Taito America Corporation */
	DRIVER( zookeep )	/* ZA  (c) 1982 Taito America Corporation */
	DRIVER( zookeep2 )	/* ZA  (c) 1982 Taito America Corporation */
	DRIVER( zookeep3 )	/* ZA  (c) 1982 Taito America Corporation */
	DRIVER( slither )	/* (c) 1982 Century II */
	DRIVER( slithera )	/* (c) 1982 Century II */
	DRIVER( complexx )	/* CX  (c) 1984 Taito America Corporation */

	/* Taito SJ System games */
	DRIVER( spaceskr )	/* EB  (c) 1981 Taito Corporation */
	DRIVER( spacecr )	/* CG  (c) 1981 Taito Corporation */
	DRIVER( junglek )	/* KN  (c) 1982 Taito Corporation */
	DRIVER( junglekj2 )	/* KN  (c) 1982 Taito Corporation */
	DRIVER( jungleh )	/* KN  (c) 1982 Taito America Corporation */
	DRIVER( junglehbr )	/* KN  (c) 1982 Taito do Brasil */
	DRIVER( piratpet )	/* KN  (c) 1982 Taito America Corporation */
	DRIVER( alpine )	/* RH  (c) 1982 Taito Corporation */
	DRIVER( alpinea )	/* RH  (c) 1982 Taito Corporation */
	DRIVER( timetunl )	/* UN  (c) 1982 Taito Corporation */
	DRIVER( wwestern )	/* WW  (c) 1982 Taito Corporation */
	DRIVER( wwestern1 )	/* WW  (c) 1982 Taito Corporation */
	DRIVER( frontlin )	/* FL  (c) 1982 Taito Corporation */
	DRIVER( elevator )	/* EA  (c) 1983 Taito Corporation */
	DRIVER( elevatorb )	/* bootleg */
	DRIVER( tinstar )	/* A10 (c) 1983 Taito Corporation */
	DRIVER( tinstar2 )	/* A10 (c) 1983 Taito Corporation */
	DRIVER( waterski )	/* A03 (c) 1983 Taito Corporation */
	DRIVER( bioatack )	/* AA8 (c) 1983 Taito Corporation + Fox Video Games license */
	DRIVER( hwrace )	/* AC4 (c) 1983 Taito Corporation */
	DRIVER( sfposeid )	/* A14 (c) 1984 Taito Corporation */
	DRIVER( kikstart )	/* A20 (c) 1984 Taito Corporation */

	/* other Taito games */
	DRIVER( fgoal )		/* TF  (c) 1979 Taito Corporation */
	DRIVER( fgoala )	/* MF  (c) 1979 Taito Corporation */
	DRIVER( crbaloon )	/* CL  (c) 1980 Taito Corporation */
	DRIVER( crbaloon2 )	/* CL  (c) 1980 Taito Corporation */
	DRIVER( sbowling )	/* KB  (c) 1982 Taito Corporation */
	DRIVER( grchamp )	/* GM  (c) 1981 Taito Corporation */
	DRIVER( marinedt )	/* MG  (c) 1981 Taito Corporation */
	DRIVER( changela )	/* ??? (c) 1983 Taito Corporation */
	DRIVER( jollyjgr )	/* KD  (c) 1982 Taito Corporation */
	DRIVER( bking )		/* DM  (c) 1982 Taito Corporation */
	DRIVER( bking2 )	/* AD6 (c) 1983 Taito Corporation */
	DRIVER( bking3 )	/* A24 (c) 1984 Taito Corporation */
	DRIVER( chaknpop )	/* A04 (c) 1983 Taito Corporation */
	DRIVER( josvolly )	/* AA  (c) 1983 Taito Corporation */
	DRIVER( gsword )	/* AC  (c) 1984 Taito Corporation */
	DRIVER( gsword2 )	/* AC  (c) 1984 Taito Corporation */
	DRIVER( pitnrun )	/* PR  (c) 1984 Taito Corporation */
	DRIVER( pitnruna )	/* PR  (c) 1984 Taito Corporation */
	DRIVER( lkage )		/* A54 (c) 1984 Taito Corporation */
	DRIVER( lkageo )	/* A54 (c) 1984 Taito Corporation */
	DRIVER( lkageoo )	/* A54 (c) 1984 Taito Corporation */
	DRIVER( lkageb )	/* bootleg */
	DRIVER( lkageb2 )	/* bootleg */
	DRIVER( lkageb3 )	/* bootleg */
	DRIVER( msisaac )	/* A34 (c) 1985 Taito Corporation */
	DRIVER( retofinv )	/* A37 (c) 1985 Taito Corporation */
	DRIVER( retofinv1 )	/* bootleg */
	DRIVER( retofinv2 )	/* bootleg */
	DRIVER( fightrol )	/* (c) 1983 Taito */
	DRIVER( rollace )	/* (c) 1983 Williams */
	DRIVER( rollace2 )	/* (c) 1983 Williams */
	DRIVER( lgp )		/* (c) 1983 Taito */
	DRIVER( vsgongf )	/* (c) 1984 Kaneko */
	DRIVER( ringfgt )	/* (c) 1984 Taito */
	DRIVER( ringfgt2 )	/* (c) 1984 Taito */
	DRIVER( fieldday )	/* A23 (c) 1984 Taito */
	DRIVER( undoukai )	/* A17 (c) 1984 Taito */
	DRIVER( 40love )	/* A30 (c) 1984 Taito */
	DRIVER( tsamurai )	/* A35 (c) 1985 Taito */
	DRIVER( tsamurai2 )	/* A35 (c) 1985 Taito */
	DRIVER( tsamuraih )	/* A35 (c) 1985 Taito */
	DRIVER( ladymstr )	/* A49 (c) 1985 Taito */
	DRIVER( nunchaku )	/* ??? (c) 1985 Taito */
	DRIVER( yamagchi )	/* A38 (c) 1985 Taito */
	DRIVER( m660 )		/* ??? (c) 1986 Taito America Corporation */
	DRIVER( m660j )		/* ??? (c) 1986 Taito Corporation (Japan) */
	DRIVER( m660b )		/* bootleg */
	DRIVER( alphaxz )	/* AZ  (c) 1986 Ed/Wood Place */
	DRIVER( buggychl )	/* A22 (c) 1984 Taito Corporation */
	DRIVER( buggychlt )	/* A22 (c) 1984 Taito Corporation + Tefri license */
	DRIVER( ssrj )		/* A40 (c) 1985 Taito Corporation */
	DRIVER( bigevglf )	/* A67 (c) 1986 Taito America Corporation (US) */
	DRIVER( bigevglfj )	/* A67 (c) 1986 Taito Corporation (Japan) */
	DRIVER( flstory )	/* A45 (c) 1985 Taito Corporation */
	DRIVER( flstoryj )	/* A45 (c) 1985 Taito Corporation (Japan) */
	DRIVER( onna34ro )	/* A52 (c) 1985 Taito Corporation (Japan) */
	DRIVER( onna34roa )	/* A52 (c) 1985 Taito Corporation (Japan) */
	DRIVER( victnine )	/* A16 (c) 1985 Taito Corporation (Japan) */
	DRIVER( gladiatr )	/* QB  (c) 1986 Taito America Corporation (US) */
	DRIVER( ogonsiro )	/* QB  (c) 1986 Taito Corporation (Japan) */
	DRIVER( greatgur )	/* QB  (c) 1986 Taito Corporation (Japan?) */
	DRIVER( ppking )	/* QO  (c) 1985 Taito America Corporation (US) */
	DRIVER( nycaptor )	/* A50 (c) 1985 Taito Corporation */
	DRIVER( cyclshtg )	/* A97 (c) 1986 Taito Corporation */
	DRIVER( bronx )		/* bootleg */
	DRIVER( colt )		/* bootleg */
	DRIVER( ksayakyu )	/* ??? (c) 1985 Taito Corporation */
	DRIVER( benberob )	/* A26 */
	DRIVER( halleys )	/* A62 (c) 1986 Taito America Corporation + Coin It (US) */
	DRIVER( halleysc )	/* A62 (c) 1986 Taito Corporation (Japan) */
	DRIVER( halleycj )	/* A62 (c) 1986 Taito Corporation (Japan) */
	DRIVER( halley87 )	/* A62 (c) 1986 Taito Corporation (Japan) */
	DRIVER( lsasquad )	/* A64 (c) 1986 Taito Corporation / Taito America (dip switch) */
	DRIVER( storming )	/* A64 (c) 1986 Taito Corporation */
	DRIVER( daikaiju )	/* A74 (c) 1986 Taito */
	DRIVER( tokio )		/* A71 1986 */
	DRIVER( tokiou )	/* A71 1986 */
	DRIVER( tokiob )	/* bootleg */
	DRIVER( bublbobl )	/* A78 (c) 1986 Taito Corporation */
	DRIVER( bublbobl1 )	/* A78 (c) 1986 Taito Corporation */
	DRIVER( bublboblr )	/* A78 (c) 1986 Taito America Corporation + Romstar license */
	DRIVER( bublboblr1 )/* A78 (c) 1986 Taito America Corporation + Romstar license */
	DRIVER( boblbobl )	/* bootleg */
	DRIVER( sboblboa )	/* bootleg */
	DRIVER( sboblbob )	/* bootleg */
	DRIVER( bub68705 )	/* bootleg */
	DRIVER( dland )		/* bootleg */
	DRIVER( missb2 )	/* bootleg on enhanced hardware */
	DRIVER( kikikai )	/* A85 (c) 1986 Taito Corporation */
	DRIVER( knightb )	/* bootleg */
	DRIVER( kicknrun )	/* A87 (c) 1986 Taito Corporation */
	DRIVER( kicknrunu )	/* A87 (c) 1986 Taito Corporation */
	DRIVER( mexico86 )	/* bootleg (Micro Research) */
	DRIVER( darius )	/* A96 (c) 1986 Taito Corporation Japan (World) */
	DRIVER( dariusj )	/* A96 (c) 1986 Taito Corporation (Japan) */
	DRIVER( dariuso )	/* A96 (c) 1986 Taito Corporation (Japan) */
	DRIVER( dariuse )	/* A96 (c) 1986 Taito Corporation (Japan) */
	DRIVER( rastan )	/* B04 (c) 1987 Taito Corporation Japan (World) */
	DRIVER( rastanu )	/* B04 (c) 1987 Taito America Corporation (US) */
	DRIVER( rastanu2 )	/* B04 (c) 1987 Taito America Corporation (US) */
	DRIVER( rastsaga )	/* B04 (c) 1987 Taito Corporation (Japan)*/
	DRIVER( rastsaga1 )	/* B04 (c) 1987 Taito Corporation (Japan)*/
	DRIVER( topspeed )	/* B14 (c) 1987 Taito Corporation Japan (World) */
	DRIVER( topspeedu )	/* B14 (c) 1987 Taito America Corporation (US) */
	DRIVER( fullthrl )	/* B14 (c) 1987 Taito Corporation (Japan) */
	DRIVER( opwolf )	/* B20 (c) 1987 Taito Corporation Japan (World) */
	DRIVER( opwolfa )	/* B20 (c) 1987 Taito Corporation Japan (World) */
	DRIVER( opwolfj )	/* B20 (c) 1987 Taito Corporation (Japan) */
	DRIVER( opwolfu )	/* B20 (c) 1987 Taito America Corporation (US) */
	DRIVER( opwolfb )	/* bootleg */
	DRIVER( othunder )	/* B67 (c) 1988 Taito Corporation Japan (World) */
	DRIVER( othunderu )	/* B67 (c) 1988 Taito America Corporation (US) */
	DRIVER( othunderuo )	/* B67 (c) 1988 Taito America Corporation (US) */
	DRIVER( othunderj )	/* B67 (c) 1988 Taito Corporation (Japan) */
	DRIVER( rainbow )	/* B22 (c) 1987 Taito Corporation */
	DRIVER( rainbowo )	/* B22 (c) 1987 Taito Corporation */
	DRIVER( rainbowe )	/* B39 (c) 1988 Taito Corporation */
	DRIVER( jumping )	/* bootleg */
	DRIVER( arkanoid )	/* A75 (c) 1986 Taito Corporation Japan (World) */
	DRIVER( arkanoidu )	/* A75 (c) 1986 Taito America Corporation + Romstar license (US) */
	DRIVER( arkanoiduo )	/* A75 (c) 1986 Taito America Corporation + Romstar license (US) */
	DRIVER( arkanoidj )	/* A75 (c) 1986 Taito Corporation (Japan) */
	DRIVER( arkmcubl )	/* bootleg */
	DRIVER( ark1ball )	/* bootleg */
	DRIVER( arkangc )	/* bootleg */
	DRIVER( arkangc2 )	/* bootleg */
	DRIVER( arkblock )	/* bootleg */
	DRIVER( arkbloc2 )	/* bootleg */
	DRIVER( arkgcbl )	/* bootleg */
	DRIVER( paddle2 )	/* bootleg */
	DRIVER( block2 )	/* bootleg */
	DRIVER( arkatayt )	/* bootleg */
	DRIVER( arktayt2 )	/* bootleg */
	DRIVER( arkatour )	/* ??? (c) 1987 Taito America Corporation + Romstar license (US) */
	DRIVER( tetrsark )	/* ??? (c) D.R.Korea */
	DRIVER( sqix )		/* B03 1987 */
	DRIVER( sqixr1 )	/* B03 1987 */
	DRIVER( sqixu )		/* B03 1987 */
	DRIVER( sqixb1 )	/* bootleg? but (c) 1987 */
	DRIVER( sqixb2 )	/* bootleg? but (c) 1987 */
	DRIVER( perestro )	/* (c) 1994 Promat */
	DRIVER( perestrof )	/* (c) 1993 Promat / Fuuki */
	DRIVER( pbillian )	/* (c) 1986 Taito */
	DRIVER( hotsmash )	/* B18 (c) 1987 Taito */
	DRIVER( exzisus )	/* B12 (c) 1987 Taito Corporation (Japan) */
	DRIVER( exzisusa )	/* B23 (c) 1987 Taito Corporation (Japan) */
	DRIVER( minivadr )	/* D26 cabinet test board */
	DRIVER( volfied )	/* C04 (c) 1989 Taito Corporation Japan (World) */
	DRIVER( volfiedu )	/* C04 (c) 1989 Taito America Corporation (US) */
	DRIVER( volfiedj )	/* C04 (c) 1989 Taito Corporation (Japan) */
	DRIVER( volfiedjo )	/* C04 (c) 1989 Taito Corporation (Japan) */
	DRIVER( bonzeadv )	/* B41 (c) 1988 Taito Corporation Japan (World) */
	DRIVER( bonzeadvo )	/* B41 (c) 1988 Taito Corporation Japan (World) */
	DRIVER( bonzeadvu )	/* B41 (c) 1988 Taito America Corporation (US) */
	DRIVER( jigkmgri )	/* B41 (c) 1988 Taito Corporation (Japan)*/
	DRIVER( asuka )		/* B68 (c) 1988 Taito Corporation (World) */
	DRIVER( asukaj )	/* B68 (c) 1988 Taito Corporation (Japan) */
	DRIVER( mofflott )	/* C17 (c) 1989 Taito Corporation (Japan) */
	DRIVER( cadash )	/* C21 (c) 1989 Taito Corporation Japan */
	DRIVER( cadashj )	/* C21 (c) 1989 Taito Corporation */
	DRIVER( cadashu )	/* C21 (c) 1989 Taito America Corporation */
	DRIVER( cadashi )	/* C21 (c) 1989 Taito Corporation Japan */
	DRIVER( cadashf )	/* C21 (c) 1989 Taito Corporation Japan */
	DRIVER( cadashg )	/* C21 (c) 1989 Taito Corporation Japan */
	DRIVER( parentj )	/* C42 (c) 199? Taito */
	DRIVER( galmedes )	/* (c) 1992 Visco (Japan) */
	DRIVER( earthjkr )	/* (c) 1993 Visco (Japan) */
	DRIVER( eto )		/* (c) 1994 Visco (Japan) */
	DRIVER( wgp )		/* C32 (c) 1989 Taito America Corporation (US) */
	DRIVER( wgpj )		/* C32 (c) 1989 Taito Corporation (Japan) */
	DRIVER( wgpjoy )	/* C32 (c) 1989 Taito Corporation (Japan) */
	DRIVER( wgpjoya )	/* C32 (c) 1989 Taito Corporation (Japan) */
	DRIVER( wgp2 )		/* C73 (c) 1990 Taito Corporation (Japan) */
	DRIVER( galastrm )	/* C99 (c) 1992 Taito Corporation */
	DRIVER( slapshot )	/* D71 (c) 1994 Taito Corporation (Japan) */
	DRIVER( opwolf3 )	/* D74 (c) 1994 Taito */
	DRIVER( opwolf3u )	/* D74 (c) 1994 Taito */
	DRIVER( scessjoe )	/* ??? (c) 1990 Wave / Taito */
	DRIVER( ashnojoe )	/* ??? (c) 1990 Wave / Taito */

	/* enhanced Z-System hardware games */
	DRIVER( gunbustr )	/* D27 (c) 1992 Taito Corporation (Japan) */
	DRIVER( superchs )	/* D46 (c) 1992 Taito America Corporation (US) */
	DRIVER( groundfx )	/* D51 (c) 1992 Taito Coporation */
	DRIVER( undrfire )	/* D67 (c) 1993 Taito Coporation Japan (World) */
	DRIVER( undrfireu )	/* D67 (c) 1993  Taito America Corporation (US) */
	DRIVER( undrfirej )	/* D67 (c) 1993 Taito Coporation (Japan) */
	DRIVER( cbombers )

	/* Toaplan games */
	DRIVER( perfrman )	/* (c) 1985 Data East Corporation (Japan) */
	DRIVER( perfrmanu )	/* (c) 1985 Data East USA (US) */
	DRIVER( tigerh )	/* A47 (c) 1985 Taito America  Corporation   GX-551 [not a Konami board!] */
	DRIVER( tigerhj )	/* A47 (c) 1985 Taito Corporation   GX-551 [not a Konami board!] */
	DRIVER( tigerhb1 )	/* bootleg but (c) 1985 Taito Corporation */
	DRIVER( tigerhb2 )	/* bootleg but (c) 1985 Taito Corporation */
	DRIVER( tigerhb3 )	/* bootleg but (c) 1985 Taito Corporation */
	DRIVER( slapfigh )	/* A76 / TP-??? */
	DRIVER( slapfigha )	/* A76 / TP-??? */
	DRIVER( slapbtjp )	/* bootleg but (c) 1986 Taito Corporation */
	DRIVER( slapbtuk )	/* bootleg but (c) 1986 Taito Corporation */
	DRIVER( slapfgtr )	/* bootleg */
	DRIVER( alcon )		/* A76 / TP-??? */
	DRIVER( getstar )	/* A68 (c) 1986 Taito Corporation */
	DRIVER( getstarj )	/* A68 (c) 1986 Taito Corporation */
	DRIVER( gtstarb1 )	/* GX-006 bootleg but (c) 1986 Taito Corporation */
	DRIVER( gtstarb2 )	/* GX-006 bootleg but (c) 1986 Taito Corporation */
	DRIVER( mjsister )	/* (c) 1986 Toaplan */

	DRIVER( fshark )	/* B02 / TP-007 (c) 1987 Taito Corporation (World) */
	DRIVER( skyshark )	/* B02 / TP-007 (c) 1987 Taito America Corporation + Romstar license (US) */
	DRIVER( hishouza )	/* B02 / TP-007 (c) 1987 Taito Corporation (Japan) */
	DRIVER( fsharkbt )	/* bootleg */
	DRIVER( wardner )	/* B25 / TP-009 (c) 1987 Taito Corporation Japan (World) */
	DRIVER( pyros )		/* B25 / TP-009 (c) 1987 Taito America Corporation (US) */
	DRIVER( wardnerj )	/* B25 / TP-009 (c) 1987 Taito Corporation (Japan) */
	DRIVER( twincobr )	/* B30 / TP-011 (c) 1987 Taito Corporation (World) */
	DRIVER( twincobru )	/* B30 / TP-011 (c) 1987 Taito America Corporation + Romstar license (US) */
	DRIVER( ktiger )	/* B30 / TP-011 (c) 1987 Taito Corporation (Japan) */
	DRIVER( gulfwar2 )	/* (c) 1991 Comad */

	DRIVER( rallybik )	/* B45 / TP-O12 (c) 1988 Taito */
	DRIVER( truxton )	/* B65 / TP-O13B (c) 1988 Taito */
	DRIVER( hellfire )	/* B90 / TP-??? (c) 1989 Toaplan + Taito license */
	DRIVER( hellfire1 )	/* B90 / TP-??? (c) 1989 Toaplan + Taito license */
	DRIVER( hellfire2 )	/* B90 / TP-??? (c) 1989 Toaplan + Taito license */
	DRIVER( hellfire3 )	/* B90 / TP-??? (c) 1989 Toaplan + Taito license */
	DRIVER( zerowing )	/* TP-O15 (c) 1989 Toaplan */
	DRIVER( zerowing2 )	/* TP-O15 (c) 1989 Toaplan */
	DRIVER( demonwld )	/* TP-O16 (c) 1990 Toaplan (+ Taito license when set to Japan) */
	DRIVER( demonwld1 )	/* TP-O16 (c) 1989 Toaplan + Taito license */
	DRIVER( demonwld2 )	/* TP-O16 (c) 1989 Toaplan */
	DRIVER( demonwld3 )	/* TP-O16 (c) 1989 Toaplan */
	DRIVER( demonwld4 )	/* TP-O16 (c) 1989 Toaplan */
	DRIVER( fireshrk )	/* TP-O17 (c) 1990 Toaplan */
	DRIVER( fireshrkd )	/* TP-O17 (c) 1990 Toaplan */
	DRIVER( fireshrkdh )	/* TP-O17 (c) 1990 Toaplan */
	DRIVER( samesame )	/* TP-O17 (c) 1989 Toaplan */
	DRIVER( samesame2 )	/* TP-O17 (c) 1989 Toaplan */
	DRIVER( outzone )	/* TP-O18 (c) 1990 Toaplan */
	DRIVER( outzonea )	/* TP-O18 (c) 1990 Toaplan */
	DRIVER( outzoneb )	/* TP-O18 (c) 1990 Toaplan */
	DRIVER( outzonec )	/* TP-O18 (c) 1990 Toaplan */
	DRIVER( vimana )	/* TP-O19 (c) 1991 Toaplan (+ Tecmo license when set to Japan) */
	DRIVER( vimana1 )	/* TP-O19 (c) 1991 Toaplan (+ Tecmo license when set to Japan)  */
	DRIVER( vimanan )	/* TP-O19 (c) 1991 Toaplan (+ Nova Apparate GMBH & Co license) */
	DRIVER( snowbros )	/* MIN16-02 (c) 1990 Toaplan + Romstar license */
	DRIVER( snowbrosa )	/* MIN16-02 (c) 1990 Toaplan + Romstar license */
	DRIVER( snowbrosb )	/* MIN16-02 (c) 1990 Toaplan + Romstar license */
	DRIVER( snowbrosc )	/* MIN16-02 (c) 1990 Toaplan + Romstar license */
	DRIVER( snowbrosj )	/* MIN16-02 (c) 1990 Toaplan */
	DRIVER( snowbrosd )	/* MIN16-02 (c) 1990 Toaplan + Dooyong license */
	DRIVER( wintbob )	/* bootleg */
	DRIVER( honeydol )	/* (c) 1995 Barko Corp */
	DRIVER( twinadv )	/* (c) 1995 Barko Corp */
	DRIVER( twinadvk )	/* (c) 1995 Barko Corp */
		/* SemiCom games on snowbros like hardware */
	DRIVER( hyperpac )	/* (c) 1995 SemiCom */
	DRIVER( hyperpacb )	/* bootleg */
	DRIVER( twinkle )	/* (c) 1997 SemiCom */
	DRIVER( toppyrap )	/* (c) 1996 SemiCom */
	DRIVER( cookbib2 )	/* (c) 1996 SemiCom */
	DRIVER( cookbib3 )	/* (c) 1997 SemiCom */
	DRIVER( 3in1semi )	/* (c) 1998 SemiCom */
	DRIVER( moremore )	/* (c) 1999 SemiCom + Exit */
	DRIVER( moremorp )	/* (c) 1999 SemiCom + Exit */
	DRIVER( 4in1boot )	/* (c) 2002 but bootleg of 1999 release? */
	DRIVER( snowbros3 )	/* (c) 2002 but hack / bootleg of snowbros? */
	DRIVER( finalttr )	/* (c) 1993 Jeil Computer System */

	/* More Toaplan Games */
	DRIVER( tekipaki )	/* TP-020 (c) 1991 Toaplan */
	DRIVER( ghox )		/* TP-021 (c) 1991 Toaplan */
	DRIVER( ghoxj )		/* TP-021 (c) 1991 Toaplan */
	DRIVER( dogyuun )	/* TP-022 (c) 1992 Toaplan */
	DRIVER( dogyuunk )	/* TP-022 (c) 1992 Toaplan */
	DRIVER( kbash )		/* TP-023 (c) 1993 Toaplan */
	DRIVER( kbash2 )	/* bootleg */
	DRIVER( truxton2 )	/* TP-024 (c) 1992 Toaplan */
	DRIVER( pipibibs )	/* TP-025 */
	DRIVER( whoopee )	/* TP-025 */
	DRIVER( pipibibi )	/* (c) 1991 Ryouta Kikaku (bootleg?) */
	DRIVER( fixeight )	/* TP-026 (c) 1992 + Taito license */
	DRIVER( fixeightb )	/* bootleg */
	DRIVER( vfive )		/* TP-027 (c) 1993 Toaplan (Japan) */
	DRIVER( grindstm )	/* TP-027 (c) 1993 Toaplan + Unite Trading license (Korea) */
	DRIVER( grindstma )	/* TP-027 (c) 1993 Toaplan + Unite Trading license (Korea) */
	DRIVER( batsugun )	/* TP-030 (c) 1993 Toaplan */
	DRIVER( batsuguna )	/* TP-030 (c) 1993 Toaplan */
	DRIVER( batsugunsp )/* TP-??? (c) 1993 Toaplan */
	DRIVER( snowbro2 )	/* TP-??? (c) 1994 Hanafram */
	DRIVER( sstriker )	/* (c) 1993 Raizing */
	DRIVER( sstrikera )	/* (c) 1993 Raizing */
	DRIVER( mahoudai )	/* (c) 1993 Raizing + Able license */
	DRIVER( shippumd )	/* (c) 1994 Raizing/8ing */
	DRIVER( kingdmgp )	/* (c) 1994 Raizing/8ing (hack?) */
	DRIVER( bgaregga )	/* (c) 1996 Raizing/8ing */
	DRIVER( bgareggahk )	/* (c) 1996 Raizing/8ing */
	DRIVER( bgareggatw )	/* (c) 1996 Raizing/8ing */
	DRIVER( bgaregganv )	/* (c) 1996 Raizing/8ing */
	DRIVER( bgareggat2 )	/* (c) 1996 Raizing/8ing */
	DRIVER( bgareggacn )	/* (c) 1996 Raizing/8ing */
	DRIVER( batrid )	/* (c) 1998 Raizing/8ing */
	DRIVER( batridu )	/* (c) 1998 Raizing/8ing */
	DRIVER( batridc )	/* (c) 1998 Raizing/8ing */
	DRIVER( batridj )	/* (c) 1998 Raizing/8ing */
	DRIVER( batridk )	/* (c) 1998 Raizing/8ing */
	DRIVER( batridja )	/* (c) 1998 Raizing/8ing */
	DRIVER( bkraidu )	/* (c) 1999 8ing */
	DRIVER( bkraiduj )	/* (c) 1999 8ing */
	DRIVER( bkraidj )	/* (c) 1999 8ing */

	/* Data East "Burger Time hardware" games */
	DRIVER( lnc )		/* (c) 1981 */
	DRIVER( zoar )		/* (c) 1982 */
	DRIVER( btime )		/* (c) 1982 */
	DRIVER( btime2 )	/* (c) 1982 */
	DRIVER( btimem )	/* (c) 1982 + Midway */
	DRIVER( tisland )	/* (c) 1982 */
	DRIVER( protennb )	/* bootleg */
	DRIVER( cookrace )	/* bootleg */
	DRIVER( wtennis )	/* bootleg 1982 */
	DRIVER( brubber )	/* (c) 1982 */
	DRIVER( bnj )		/* (c) 1982 + Midway */
	DRIVER( caractn )	/* bootleg */
	DRIVER( disco )		/* (c) 1982 */
	DRIVER( discof )	/* (c) 1982 */
	DRIVER( sdtennis )	/* (c) 1983 */
	DRIVER( mmonkey )	/* (c) 1982 Technos Japan + Roller Tron */

		/* cassette system, parent is decocass */
	DRIVER( decocass )
	DRIVER( ctsttape )	/* ? */
	DRIVER( chwy )		/* 01 1980.12 Highway Chase */
						/* 02 1980.12 Sengoku Ninjatai */
						/* 03 1981.01 Manhattan */
	DRIVER( cterrani )	/* 04 1981.02 Terranian */
						/* 05 1981.?? Missile Sprinter */
						/* 06 1980.12 Nebbler */
	DRIVER( castfant )	/* 07 1981.02 Astro Fantasia */
						/* 08 1981.03 The Tower */
	DRIVER( csuperas )	/* 09 1981.05 Super Astro Fighter */
						/* 10 1981.?? Ocean to Ocean (medal) */
	DRIVER( clocknch )	/* 11 1981.04 Rock'n Chase */
						/* 12 1981.08 Flash Boy/DECO Kid */
	DRIVER( cprogolf )	/* 13 1981.08 Pro Golf */
						/* 14 1981.06 DS Telejan */
	DRIVER( cluckypo )	/* 15 1981.?? Lucky Poker */
	DRIVER( ctisland )	/* 16 1982.02 Treasure Island */
	DRIVER( ctisland2 )	/* 16 */
	DRIVER( ctisland3 )	/* 16 */
						/* 17 1981.10 Bobbit */
	DRIVER( cexplore )	/* 18 1982.02 Explorer */
	DRIVER( cdiscon1 )	/* 19 1982.04 Disco No.1 */
	DRIVER( csweetht )	/* 19 */
	DRIVER( ctornado )	/* 20 1982.05 Tornado */
	DRIVER( cmissnx )	/* 21 1982.04 Mission X/Zoar */
	DRIVER( cptennis )	/* 22 1982.06 Pro Tennis */
						/* 23 1982.?? 18 Hole Pro Golf */
						/* 24 1982.07 Tsumego Kaisyou */
						/* 25 1982.10 Fishing */
	DRIVER( cbtime )	/* 26 1982.08 Hamburger/Burger Time */
	DRIVER( cburnrub )	/* 27 1982.11 Burnin' Rubber/Bump'n Jump */
	DRIVER( cburnrub2 )	/* 27 */
	DRIVER( cbnj )		/* 27 */
	DRIVER( cgraplop )	/* 28 1982.11 Grapelop */
	DRIVER( cgraplop2 )	/* 28 */
	DRIVER( clapapa )	/* 29 1982.11 Lapapa/Rootin' Tootin' */
	DRIVER( clapapa2 )	/* 29 */ /* this one doesn't display lapapa anyehere */
						/* 30 1983.03 Skater */
	DRIVER( cprobowl )	/* 31 1983.03 Pro Bowling */
	DRIVER( cnightst )	/* 32 1983.04 Night Star */
	DRIVER( cnightst2 )	/* 32 */
	DRIVER( cprosocc )	/* 33 1982.08 Pro Soccer */
						/* 34 1983.09 Super Doubles Tennis */
	DRIVER( cflyball )	/* 35 1983.?? Bampoline/Flying Ball */
						/* 36 1984.04 Genesis/Boomer Rang'r */
	DRIVER( czeroize )	/* 37 1983.10 Zeroize */ /* doesn't work at all */
	DRIVER( cscrtry )	/* 38 1984.03 Scrum Try */
	DRIVER( cscrtry2 )	/* 38 */
	DRIVER( cppicf )	/* 39 1984.02 Peter Pepper's Ice Cream Factory */
	DRIVER( cppicf2 )	/* 39 */
	DRIVER( cfghtice )	/* 40 1984.04 Fighting Ice Hockey */
						/* 41 1984.05 Oozumou */
						/* 42 1984.08 Hellow Gateball */ /* not a typo, this is official spelling */
						/* 43 1984.08 Yellow Cab */
	DRIVER( cbdash )	/* 44 1985.08 Boulder Dash */
						/* UX7 1984.12 Tokyo Mie Shinryoujo */
						/* UX8 1985.01 Tokyo Mie Shinryoujo Part 2 */
						/* UX9 1985.05 Geinoujin Shikaku Shiken */

	/* Data East LD games */
	DRIVER( cobra )		/* (c) 1984 */
	DRIVER( rblaster )	/* (c) 1985 */

	/* other Data East games */
	DRIVER( madalien )	/* (c) 1980 */
	DRIVER( madaliena )	/* (c) 1980 */
	DRIVER( astrof )	/* (c) [1980?] */
	DRIVER( astrof2 )	/* (c) [1980?] */
	DRIVER( astrof3 )	/* (c) [1980?] */
	DRIVER( abattle )	/* Sidam */
	DRIVER( abattle2 )	/* Sidam */
	DRIVER( afire )		/* Rene Pierre */
	DRIVER( acombat )	/* bootleg */
	DRIVER( acombato )	/* bootleg */
	DRIVER( sstarbtl )	/* bootleg */
	DRIVER( spfghmk2 )	/* (c) [1979] Data East Corporation */
	DRIVER( spfghmk22 )	/* (c) [1979] Data East Corporation */
	DRIVER( tomahawk )	/* (c) 1980 Data East, Inc. */
	DRIVER( tomahawk1 )	/* (c) 1980 Data East, Inc. */
	DRIVER( progolf )	/* (c) 1981 */
	DRIVER( progolfa )	/* (c) 1981 */
	DRIVER( deshoros )	/* (c) 1983 */
	DRIVER( prosoccr )	/* (c) 1983 */
	DRIVER( prosport )	/* (c) 1983 */
	DRIVER( prosporta )	/* (c) 1983 */
	DRIVER( boomrang )	/* (c) 1983 */
	DRIVER( boomranga )	/* (c) 1983 */
	DRIVER( kamikcab )	/* (c) 1984 */
	DRIVER( yellowcbj )	/* (c) 1984 */
	DRIVER( yellowcbb )	/* bootleg */
	DRIVER( liberate )	/* (c) 1984  Data East Corporation */
	DRIVER( dualaslt )	/* (c) 1984  Data East USA (US) */
	DRIVER( liberateb )	/* bootleg */
	DRIVER( bwings )	/* (c) 1984 */
	DRIVER( bwingso )	/* (c) 1984 */
	DRIVER( bwingsa )	/* (c) 1984 */
	DRIVER( zaviga )	/* (c) */
	DRIVER( zavigaj )	/* (c) */
	DRIVER( kchamp )	/* (c) 1984 Data East USA (US) */
	DRIVER( karatedo )	/* (c) 1984 Data East Corporation (Japan) */
	DRIVER( kchampvs )	/* (c) 1984 Data East USA (US) */
	DRIVER( kchampvs2 ) /* (c) 1984 Data East USA (US) */
	DRIVER( karatevs )	/* (c) 1984 Data East Corporation (Japan) */
	DRIVER( compgolf )	/* (c) 1985 Data East Corporation (Japan) */
	DRIVER( compgolfo )	/* (c) 1985 Data East Corporation (Japan) */
	DRIVER( cntsteer )	/* (c) 1985 Data East Corporation */
	DRIVER( zerotrgt )	/* (c) 1985 Data East Corporation */
	DRIVER( gekitsui )	/* (c) 1985 Data East Corporation (Japan) */
	DRIVER( tryout )	/* (c) 1985 Data East Corporation (Japan) */
	DRIVER( firetrap )	/* (c) 1986 Data East USA (US) */
	DRIVER( firetpbl )	/* bootleg */
	DRIVER( metlclsh )	/* (c) 1985 Data East */
	DRIVER( chanbara )	/* (c) 1985 Data East */
	DRIVER( brkthru )	/* (c) 1986 Data East USA (US) */
	DRIVER( brkthruj )	/* (c) 1986 Data East Corporation (Japan) */
	DRIVER( forcebrk )	/* (c) 1986 Data East Corporation (Japan) */
	DRIVER( darwin )	/* (c) 1986 Data East Corporation (Japan) */
	DRIVER( shootout )	/* (c) 1985 Data East USA (US) */
	DRIVER( shootoutj )	/* (c) 1985 Data East USA (Japan) */
	DRIVER( shootoutb )	/* bootleg */
	DRIVER( sidepckt )	/* (c) 1986 Data East Corporation */
	DRIVER( sidepcktj )	/* (c) 1986 Data East Corporation */
	DRIVER( sidepcktb )	/* bootleg */
	DRIVER( exprraid )	/* (c) 1986 Data East USA (US) */
	DRIVER( exprraida )	/* (c) 1986 Data East USA (US) */
	DRIVER( wexpress )	/* (c) 1986 Data East Corporation (World?) */
	DRIVER( wexpressb )	/* bootleg */
	DRIVER( wexpressb2 )	/* bootleg */
	DRIVER( pcktgal )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( pcktgalb )	/* bootleg */
	DRIVER( pcktgal2 )	/* (c) 1989 Data East Corporation (World?) */
	DRIVER( pcktgal2j )	/* (c) 1989 Data East Corporation (World?) */
	DRIVER( pokechmp )	/* Korean hack of Pocket Gal */
	DRIVER( spool3 )	/* (c) 1989 Data East Corporation (World?) */
	DRIVER( spool3i )	/* (c) 1990 Data East Corporation + I-Vics license */
	DRIVER( battlera )	/* (c) 1988 Data East Corporation (World) */
	DRIVER( bldwolf )	/* (c) 1988 Data East USA (US) */
	DRIVER( bldwolfj )	/* (c) 1988 Data East Corporation (Japan) */
	DRIVER( actfancr )	/* (c) 1989 Data East Corporation (World) */
	DRIVER( actfancr1 )	/* (c) 1989 Data East Corporation (World) */
	DRIVER( actfancrj )	/* (c) 1989 Data East Corporation (Japan) */
	DRIVER( triothep )	/* (c) 1989 Data East Corporation (World) */
	DRIVER( triothepj )	/* (c) 1989 Data East Corporation (Japan) */

	/* Data East 8-bit games */
	DRIVER( lastmisn )	/* (c) 1986 Data East USA (US) */
	DRIVER( lastmisno )	/* (c) 1986 Data East USA (US) */
	DRIVER( lastmisnj )	/* (c) 1986 Data East Corporation (Japan) */
	DRIVER( shackled )	/* (c) 1986 Data East USA (US) */
	DRIVER( breywood )	/* (c) 1986 Data East Corporation (Japan) */
	DRIVER( csilver )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( csilverj )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( ghostb )	/* (c) 1987 Data East USA (US) */
	DRIVER( ghostb3 )	/* (c) 1987 Data East USA (US) */
	DRIVER( meikyuh )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( meikyuha )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( srdarwin )	/* (c) 1987 Data East Corporation (World) */
	DRIVER( srdarwinj )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( gondo )		/* (c) 1987 Data East USA (US) */
	DRIVER( makyosen )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( garyoret )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( cobracom )	/* (c) 1988 Data East Corporation (World) */
	DRIVER( cobracomj )	/* (c) 1988 Data East Corporation (Japan) */
	DRIVER( oscar )		/* (c) 1988 Data East Corporation (World) */
	DRIVER( oscaru )	/* (c) 1987 Data East USA (US) */
	DRIVER( oscarj1 )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( oscarj2 )	/* (c) 1987 Data East Corporation (Japan) */

	/* Data East 16-bit games */
	DRIVER( karnov )	/* (c) 1987 Data East USA (US) */
	DRIVER( karnovj )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( wndrplnt )	/* (c) 1987 Data East Corporation (Japan) */
	DRIVER( chelnov )	/* (c) 1988 Data East USA (World) */
	DRIVER( chelnovu )	/* (c) 1988 Data East USA (US) */
	DRIVER( chelnovj )	/* (c) 1988 Data East Corporation (Japan) */
		/* the following ones all run on similar hardware */
	DRIVER( hbarrel )	/* (c) 1987 Data East USA (US) */
	DRIVER( hbarrelw )	/* (c) 1987 Data East Corporation (World) */
	DRIVER( baddudes )	/* (c) 1988 Data East USA (US) */
	DRIVER( drgninja )	/* (c) 1988 Data East Corporation (Japan) */
	DRIVER( birdtry )	/* (c) 1988 Data East Corporation (Japan) */
	DRIVER( robocop )	/* (c) 1988 Data East Corporation (World) */
	DRIVER( robocopw )	/* (c) 1988 Data East Corporation (World) */
	DRIVER( robocopj )	/* (c) 1988 Data East Corporation (Japan) */
	DRIVER( robocopu )	/* (c) 1988 Data East USA (US) */
	DRIVER( robocopu0 )	/* (c) 1988 Data East USA (US) */
	DRIVER( robocopb )	/* bootleg */
	DRIVER( automat )	/* bootleg */
	DRIVER( hippodrm )	/* (c) 1989 Data East USA (US) */
	DRIVER( ffantasy )	/* (c) 1989 Data East Corporation (Japan) */
	DRIVER( ffantasya )	/* (c) 1989 Data East Corporation (Japan) */
	DRIVER( slyspy )	/* (c) 1989 Data East USA (US) */
	DRIVER( slyspy2 )	/* (c) 1989 Data East USA (US) */
	DRIVER( secretag )	/* (c) 1989 Data East Corporation (World) */
	DRIVER( secretab )	/* bootleg */
	DRIVER( midres )	/* (c) 1989 Data East Corporation (World) */
	DRIVER( midresu )	/* (c) 1989 Data East USA (US) */
	DRIVER( midresj )	/* (c) 1989 Data East Corporation (Japan) */
	DRIVER( midresb )	/* (c) 1989 Data East Corporation (Japan) */
	DRIVER( bouldash )	/* (c) 1990 Data East Corporation (World) */
	DRIVER( bouldashj )	/* (c) 1990 Data East Corporation (Japan) */
		/* end of similar hardware */
	DRIVER( stadhero )	/* (c) 1988 Data East Corporation (Japan) */
	DRIVER( madmotor )	/* (c) [1989] Mitchell */
		/* All these games have a unique code stamped on the mask roms */
	DRIVER( vaportra )	/* MAA (c) 1989 Data East Corporation (World) */
	DRIVER( vaportrau )	/* MAA (c) 1989 Data East Corporation (US) */
	DRIVER( kuhga )		/* MAA (c) 1989 Data East Corporation (Japan) */
	DRIVER( cbuster )	/* MAB (c) 1990 Data East Corporation (World) */
	DRIVER( cbusterw )	/* MAB (c) 1990 Data East Corporation (World) */
	DRIVER( cbusterj )	/* MAB (c) 1990 Data East Corporation (Japan) */
	DRIVER( twocrude )	/* MAB (c) 1990 Data East USA (US) */
	DRIVER( darkseal )	/* MAC (c) 1990 Data East Corporation (World) */
	DRIVER( darkseal1 )	/* MAC (c) 1990 Data East Corporation (World) */
	DRIVER( darksealj )	/* MAC (c) 1990 Data East Corporation (Japan) */
	DRIVER( gatedoom )	/* MAC (c) 1990 Data East Corporation (US) */
	DRIVER( gatedoom1 )	/* MAC (c) 1990 Data East Corporation (US) */
	DRIVER( edrandy )	/* MAD (c) 1990 Data East Corporation (World) */
	DRIVER( edrandy2 )	/* MAD (c) 1990 Data East Corporation (World) */
	DRIVER( edrandy1 )	/* MAD (c) 1990 Data East Corporation (World) */
	DRIVER( edrandyj )	/* MAD (c) 1990 Data East Corporation (Japan) */
	DRIVER( supbtime )	/* MAE (c) 1990 Data East Corporation (World) */
	DRIVER( supbtimea )	/* MAE (c) 1990 Data East Corporation (World) */
	DRIVER( supbtimej )	/* MAE (c) 1990 Data East Corporation (Japan) */
	DRIVER( mutantf )	/* MAF (c) 1992 Data East Corporation (World) */
	DRIVER( mutantf4 )	/* MAF (c) 1992 Data East Corporation (World) */
	DRIVER( mutantf3 )	/* MAF (c) 1992 Data East Corporation (World) */
	DRIVER( deathbrd )	/* MAF (c) 1992 Data East Corporation (Japan) */
	DRIVER( cninja )	/* MAG (c) 1991 Data East Corporation (World) */
	DRIVER( cninja1 )	/* MAG (c) 1991 Data East Corporation (World) */
	DRIVER( cninjau )	/* MAG (c) 1991 Data East Corporation (US) */
	DRIVER( joemac )	/* MAG (c) 1991 Data East Corporation (Japan) */
	DRIVER( stoneage )	/* bootleg */
	DRIVER( robocop2 )	/* MAH (c) 1991 Data East Corporation (World) */
	DRIVER( robocop2u )	/* MAH (c) 1991 Data East Corporation (US) */
	DRIVER( robocop2j )	/* MAH (c) 1991 Data East Corporation (Japan) */
	DRIVER( thndzone )	/* MAJ (c) 1991 Data East Corporation (World) */
	DRIVER( dassault )	/* MAJ (c) 1991 Data East Corporation (US) */
	DRIVER( dassault4 )	/* MAJ (c) 1991 Data East Corporation (US) */
	DRIVER( chinatwn )	/* MAK (c) 1991 Data East Corporation (Japan) */
	DRIVER( rohga )		/* MAM (c) 1991 Data East Corporation (Asia/Euro) */
	DRIVER( rohga1 )	/* MAM (c) 1991 Data East Corporation (Asia/Euro) */
	DRIVER( rohga2 )	/* MAM (c) 1991 Data East Corporation (Asia/Euro) */
	DRIVER( rohgah )	/* MAM (c) 1991 Data East Corporation (Hong Kong) */
	DRIVER( rohgau )	/* MAM (c) 1991 Data East Corporation (US) */
	DRIVER( wolffang )	/* MAM (c) 1991 Data East Corporation (Japan) */
	DRIVER( schmeisr )	/*     (c) 1993 Hot B */
	DRIVER( captaven )	/* MAN (c) 1991 Data East Corporation (Asia) */
	DRIVER( captavena )	/* MAN (c) 1991 Data East Corporation (Asia) */
	DRIVER( captavene )	/* MAN (c) 1991 Data East Corporation (UK) */
	DRIVER( captavenu )	/* MAN (c) 1991 Data East Corporation (US) */
	DRIVER( captavenuu )	/* MAN (c) 1991 Data East Corporation (US) */
	DRIVER( captavenua )	/* MAN (c) 1991 Data East Corporation (US) */
	DRIVER( captavenj )	/* MAN (c) 1991 Data East Corporation (Japan) */
						/* MAO ?? */
	DRIVER( tumblep )	/* MAP (c) 1991 Data East Corporation (World) */
	DRIVER( tumblepj )	/* MAP (c) 1991 Data East Corporation (Japan) */
	DRIVER( tumbleb )	/* bootleg */
	DRIVER( tumbleb2 )	/* bootleg */
	DRIVER( jumpkids )	/* (c) 1993 Comad */
	DRIVER( jumppop )	/* (c) 2001 ESD */
	DRIVER( pangpang )	/* (c) 1994 Dong Gue La Mi Ltd. */
	DRIVER( sdfight )	/* (c) 1996 SemiCom */
	DRIVER( wlstar )	/* (c) 1995 Mijin */
	DRIVER( wondl96 )	/* (c) 1996 SemiCom */
	DRIVER( fncywld )	/* (c) 1996 Unico */
	DRIVER( htchctch )	/* (c) 1995 SemiCom */
	DRIVER( cookbib )	/* (c) 1995 SemiCom */
	DRIVER( chokchok )	/* (c) 1995 SemiCom */
	DRIVER( metlsavr )	/* (c) 1994 */
	DRIVER( bcstry )	/* (c) 1997 SemiCom */
	DRIVER( bcstrya )	/* (c) 1997 SemiCom */
	DRIVER( semibase )	/* (c) 1997 SemiCom */
	DRIVER( dquizgo )	/* (c) 1998 SemiCom */
	DRIVER( suprtrio )	/* (c) 1994 GameAce */
	DRIVER( lemmings )	/* prototype (c) 1991 Data East USA (US) */
						/* MAQ ?? */
	DRIVER( dragngun )	/* MAR (c) 1992 Data East Corporation (US) */
	DRIVER( wizdfire )	/* MAS (c) 1992 Data East Corporation (Over Sea) */
	DRIVER( wizdfireu )	/* MAS (c) 1992 Data East Corporation (US) */
	DRIVER( darkseal2 )	/* MAS (c) 1992 Data East Corporation (Japan) */
	DRIVER( funkyjet )	/* MAT (c) 1992 Mitchell */
	DRIVER( funkyjetj )	/* MAT (c) 1992 Mitchell */
						/* MAU ?? */
	DRIVER( nitrobal )	/* MAV (c) 1992 Data East Corporation (US) */
	DRIVER( gunball )	/* MAV (c) 1992 Data East Corporation (Japan) */
						/* MAW ?? */
						/* MAX ?? */
	DRIVER( dietgo )	/* MAY (c) 1993 */
	DRIVER( dietgoe )	/* MAY (c) 1993 */
	DRIVER( dietgou )	/* MAY (c) 1993 */
	DRIVER( dietgoj )	/* MAY (c) 1993 */
	DRIVER( pktgaldx )	/* MAZ (c) 1993 Data East (Euro v3.00) */
	DRIVER( pktgaldxj )	/* MAZ (c) 1993 */
	DRIVER( pktgaldxb )	/* bootleg */
						/* MBA ?? */
						/* MBB ?? */
						/* MBC ?? */
	DRIVER( boogwing )	/* MBD (c) 1992 (Euro) */
	DRIVER( boogwinga )	/* MBD (c) 1992 (Asia) */
	DRIVER( ragtime )	/* MBD (c) 1992 (Japan) */
	DRIVER( ragtimea )	/* MBD (c) 1992 (Japan) */
	DRIVER( dblewing )	/* MBE (c) 1993 Mitchell */
	DRIVER( fghthist )	/* MBF (c) 1993 Data East Corporation (World) */
	DRIVER( fghthistu )	/* MBF (c) 1993 Data East Corporation (US) */
	DRIVER( fghthista )	/* MBF (c) 1993 Data East Corporation (US) */
	DRIVER( fghthistj )	/* MBF (c) 1993 Data East Corporation (Japan) */
	DRIVER( hvysmsh )	/* MBG (c) 1993 Data East Corporation (World) */
	DRIVER( hvysmsha )	/* MBG (c) 1993 Data East Corporation (Asia) */
	DRIVER( hvysmshj )	/* MBG (c) 1993 Data East Corporation (Japan) */
	DRIVER( nslasher )	/* MBH (c) 1993 Data East Corporation */
	DRIVER( nslasherj )	/* MBH (c) 1993 Data East Corporation (Japan)*/
	DRIVER( nslashers )	/* MBH (c) 1993 Data East Corporation (Japan)*/
						/* MBI ?? */
						/* MBJ ?? */
						/* MBK ?? */
						/* MBL ?? */
	DRIVER( lockload )	/* MBM (c) 1994 Data East Corporation (US) */
	DRIVER( lockloadu )	/* MBM (c) 1994 Data East Corporation (US) */
	DRIVER( joemacr )	/* MBN (c) 1994 */
	DRIVER( joemacra )	/* MBN (c) 1994 */
						/* MBO ?? */
						/* MBP ?? */
						/* MBQ ?? */
	DRIVER( tattass )	/* prototype (c) 1994 Data East Pinball (US) */
	DRIVER( tattassa )	/* prototype (c) 1994 Data East Pinball (Asia) */
	DRIVER( charlien )	/* MBR (c) 1994 Mitchell */
						/* MBS ?? */
						/* MBT ?? */
						/* MBU ?? */
						/* MBV ?? */
						/* MBW ?? */
	DRIVER( wcvol95 )	/* MBX (c) 1993 Data East */
						/* MBY ?? */
	DRIVER( backfire )	/* MBZ (c) 1995 */
	DRIVER( backfirea )	/* MBZ (c) 1995 */
						/* MCA ?? */
	DRIVER( prtytime )	/* MCB (c) 1995 Mitchell */
	DRIVER( gangonta )	/* MCB (c) 1995 Mitchell */
	DRIVER( chainrec )	/* MCC (c) 1994 */
	DRIVER( magdrop )	/* MCC (c) 1995 Data East */
	DRIVER( magdropp )	/* MCC (c) 1995 Data East */
						/* MCD ?? */
	/* MCE Dunk Dream 95/Hoops96 See MLC games below */
	DRIVER( osman )		/* MCF (c) 1996 Mitchell */
	DRIVER( candance )	/* MCF (c) 1996 Mitchell */
	DRIVER( sotsugyo )	/*     (c) 1995 Mitchell (Atlus license) */
	DRIVER( sshangha )	/*     (c) 1992 Hot-B */
	DRIVER( sshanghab )	/* bootleg */

	/* Data East MLC Games */
	DRIVER( hoops96 )	/* MCE (c) 1996 Data East Corporation */
	DRIVER( ddream95 )	/* MCE (c) 1996 Data East Corporation */
	DRIVER( hoops95 )	/* MCE (c) 1996 Data East Corporation */
	DRIVER( avengrgs )	/* MCG (c) 1995 Data East Corporation (World) */
	DRIVER( avengrgsj )	/* MCG (c) 1995 Data East Corporation (Japan) */
	DRIVER( skullfng )	/* MCH (c) 1996 Data East Corporation (World) */
	DRIVER( skullfngj )	/* MCH (c) 1996 Data East Corporation (Japan) */
	DRIVER( stadhr96 )	/* MCM (c) 1996 Data East */
	DRIVER( stadhr96a )	/* MCM (c) 1996 Data East */

	/* Atari b/w games */
	DRIVER( tank8 )		/* ??????           1976/04 [6800] */
	DRIVER( tank8a )	/* ??????           1976/04 [6800] */
	DRIVER( tank8b )	/* ??????           1976/04 [6800] */
	DRIVER( tank8c )	/* ??????           1976/04 [6800] */
	DRIVER( tank8d )	/* ??????           1976/04 [6800] */
	DRIVER( cball )		/* ?????? prototype 1976/?? [6800] */
	DRIVER( copsnrob )	/* 005625           1976/07 [6502] */
	DRIVER( flyball )	/* 005629           1976/07 [6502] */
	DRIVER( sprint2 )	/* 005922           1976/11 [6502] */
	DRIVER( sprint2a )	/* 005922           1976/11 [6502] */
	DRIVER( sprint4 )	/* 008716           1977/12 [6502] */
	DRIVER( sprint4a )	/* 008716           1977/12 [6502] */
	DRIVER( nitedrvr )	/* 006321           1976/10 [6502] */
	DRIVER( dominos )	/* 007305           1977/01 [6502] */
	DRIVER( triplhnt )	/* 008422-008791    1977/04 [6800] */
	DRIVER( sprint8 )	/* ??????           1977/05 [6800] */
	DRIVER( sprint8a )	/* ??????           1977/05 [6800] */
	DRIVER( dragrace )	/* 008505-008521    1977/06 [6800] */
	DRIVER( poolshrk )	/* 006281           1977/06 [6800] */
	DRIVER( starshp1 )	/* 007513-007531    1977/07 [6502] */
	DRIVER( starshpp )	/* 007513-007531    1977/07 [6502] */
	DRIVER( superbug )	/* 009115-009467    1977/09 [6800] */
	DRIVER( canyon )	/* 009493-009504    1977/10 [6502] */
	DRIVER( canyonp )	/* 009493-009504    1977/10 [6502] */
	DRIVER( destroyr )	/* 030131-030136    1977/10 [6800] */
	DRIVER( sprint1 )	/* 006443           1978/01 [6502] */
	DRIVER( ultratnk )	/* 009801           1978/02 [6502] */
	DRIVER( skyraid )	/* 009709           1978/03 [6502] */
	DRIVER( tourtabl )	/* 030170           1978/03 [6507] */
	DRIVER( tourtab2 )	/* 030170           1978/03 [6507] */
	DRIVER( avalnche )	/* 030574           1978/04 [6502] */
	DRIVER( cascade )	/* bootleg                         */
	DRIVER( firetrk )	/* 030926           1978/06 [6808] */
	DRIVER( skydiver )	/* 009787           1978/06 [6800] */
	/* Smokey Joe */	/* 030926           1978/07 [6502] */
	DRIVER( sbrkout )	/* 033442-033455    1978/09 [6502] */
	DRIVER( atarifb )	/* 033xxx           1978/10 [6502] */
	DRIVER( atarifb1 )	/* 033xxx           1978/10 [6502] */
	DRIVER( orbit )		/* 033689-033702    1978/11 [6800] */
	DRIVER( boxer )		/* ?????? prototype 1978    [6502] */
	DRIVER( wolfpack )	/* ?????? prototype         [6502] */
	DRIVER( mgolf )		/* ?????? prototype 1978    [6502] */
	DRIVER( videopin )	/* 034253-034267    1979/02 [6502] */
	DRIVER( atarifb4 )	/* 034754           1979/04 [6502] */
	DRIVER( subs )		/* 033714           1979/05 [6502] */
	DRIVER( bsktball )	/* 034756-034766    1979/05 [6502] */
	DRIVER( abaseb )	/* 034711-034738    1979/06 [6502] */
	DRIVER( abaseb2 )	/* 034711-034738    1979/06 [6502] */
	DRIVER( montecar )	/* 035763-035780    1980/04 [6502] */
	DRIVER( soccer )	/* 035222-035260    1980/04 [6502] */

	/* Atari "Missile Command hardware" games */
	DRIVER( missile )	/* 035820-035825    (c) 1980 */
	DRIVER( missile2 )	/* 035820-035825    (c) 1980 */
	DRIVER( suprmatk )	/*                  (c) 1980 + (c) 1981 Gencomp */
	DRIVER( suprmatkd )	/*                  (c) 1980 + (c) 1981 Gencomp */
	DRIVER( mcombat )
	DRIVER( mcombata )

	/* Atari vector games */
	DRIVER( llander )	/* 0345xx           no copyright notice */
	DRIVER( llander1 )	/* 0345xx           no copyright notice */
	DRIVER( asteroid )	/* 035127-035145    (c) 1979 */
	DRIVER( asteroid2 )	/* 035127-035145    (c) 1979 */
	DRIVER( asteroid1 )	/* 035127-035145    no copyright notice */
	DRIVER( asteroidb )	/* (bootleg) */
	DRIVER( asterock )	/* Sidam bootleg    (c) 1979 */
	DRIVER( meteorts )	/* VCC bootleg      (c) 1979 */
	DRIVER( meteorho )	/* Hoei? bootleg    (c) 1980 */
	DRIVER( astdelux )	/* 0351xx           (c) 1980 */
	DRIVER( astdelux2 )	/* 0351xx           (c) 1980 */
	DRIVER( astdelux1 )	/* 0351xx           (c) 1980 */
	DRIVER( bzone )		/* 0364xx           (c) 1980 */
	DRIVER( bzone2 )	/* 0364xx           (c) 1980 */
	DRIVER( bzonec )	/* 0364xx           (c) 1980 */
	DRIVER( bradley )	/*     ??           (c) 1980 */
	DRIVER( redbaron )	/* 036995-037007    (c) 1980 */
	DRIVER( tempest )	/* 136002           (c) 1980 */
	DRIVER( tempest1 )	/* 136002           (c) 1980 */
	DRIVER( tempest2 )	/* 136002           (c) 1980 */
	DRIVER( tempest3 )	/* 136002           (c) 1980 */
	DRIVER( temptube )	/* (hack) */
	DRIVER( spacduel )	/* 136006           (c) 1980 */
	DRIVER( gravitar )	/* 136010           (c) 1982 */
	DRIVER( gravitar2 )	/* 136010           (c) 1982 */
	DRIVER( gravp )		/* (proto)          (c) 1982 */
	DRIVER( lunarbat )	/* (proto)          (c) 1982 */
	DRIVER( lunarba1 )	/* (proto)          (c) 1982 */
	DRIVER( quantum )	/* 136016           (c) 1982 */	/* made by Gencomp */
	DRIVER( quantum1 )	/* 136016           (c) 1982 */	/* made by Gencomp */
	DRIVER( quantump )	/* 136016           (c) 1982 */	/* made by Gencomp */
	DRIVER( bwidow )	/* 136017           (c) 1982 */
	DRIVER( starwars )	/* 136021           (c) 1983 */
	DRIVER( starwars1 )	/* 136021           (c) 1983 */
	DRIVER( tomcatsw )	/* (proto)          (c) 1983 */
	DRIVER( mhavoc )	/* 136025           (c) 1983 */
	DRIVER( mhavoc2 )	/* 136025           (c) 1983 */
	DRIVER( mhavocp )	/* 136025           (c) 1983 */
	DRIVER( mhavocrv )	/* (hack) */
	DRIVER( alphaone )	/* (proto)          (c) 1983 */
	DRIVER( alphaonea )	/* (proto)          (c) 1983 */
	DRIVER( esb )		/* 136031           (c) 1985 */
	DRIVER( tomcat )	/* (proto)          (c) 1985 */

	/* Atari "Centipede hardware" games */
	DRIVER( warlords )	/* 037153-037159    (c) 1980 */
	DRIVER( centiped )	/* 136001           (c) 1980 */
	DRIVER( centiped2 )	/* 136001           (c) 1980 */
	DRIVER( centtime )	/* 136001           (c) 1980 */
	DRIVER( centipdb )	/* (bootleg) */
	DRIVER( centipdd )	/* hack by Two Bit Score */
	DRIVER( caterplr )	/* (bootleg) */
	DRIVER( millpac )	/* Valadon */
	DRIVER( magworm )	/* (bootleg) */
	DRIVER( mazeinv ) 	/* (proto)          (c) 1982 */
	DRIVER( milliped )	/* 136013           (c) 1982 */
	DRIVER( millipdd )	/* hack by Two Bit Score */
	DRIVER( qwak )	 	/* (proto)          (c) 1982 */
	DRIVER( runaway )	/* (proto)          (c) 1982 */
	DRIVER( bullsdrt )	/* (c) 1985 Shinkai */
	DRIVER( cmmb162 )

	/* misc Atari games */
	DRIVER( tunhunt )	/* 136000           (c) 1979 */
	DRIVER( tunhuntc )	/* 136000           (c) 1981 */ /* licensed to / distributed by Centuri */
	DRIVER( liberatr )	/* 136012           (c) 1982 */
	DRIVER( liberatr2 )	/* 136012           (c) 1982 */
	DRIVER( foodf )		/* 136020           (c) 1982 */	/* made by Gencomp */
	DRIVER( foodf2 )	/* 136020           (c) 1982 */	/* made by Gencomp */
	DRIVER( foodfc )	/* 136020           (c) 1982 */	/* made by Gencomp */
	DRIVER( ccastles )	/* 136022           (c) 1983 */
	DRIVER( ccastlesg )	/* 136022           (c) 1983 */
	DRIVER( ccastlesp )	/* 136022           (c) 1983 */
	DRIVER( ccastlesf )	/* 136022           (c) 1983 */
	DRIVER( ccastles3 )	/* 136022           (c) 1983 */
	DRIVER( ccastles2 )	/* 136022           (c) 1983 */
	DRIVER( ccastles1 )	/* 136022           (c) 1983 */
	DRIVER( ccastlesj )	/* 136022           (c) 1983 */
	DRIVER( cloak )		/* 136023           (c) 1983 */
	DRIVER( cloaksp )	/* 136023           (c) 1983 */
	DRIVER( cloakfr )	/* 136023           (c) 1983 */
	DRIVER( cloakgr )	/* 136023           (c) 1983 */
	DRIVER( agentx4 )	/* 136023           (c) 1983 */
	DRIVER( agentx3 )	/* 136023           (c) 1983 */
	DRIVER( agentx2 )	/* 136023           (c) 1983 */
	DRIVER( agentx1 )	/* 136023           (c) 1983 */
	DRIVER( cloud9 )	/* (proto)          (c) 1983 */
	DRIVER( firebeas )	/* (proto)          (c) 1983 */
	DRIVER( firefox )	/* 136026           (c) 1984 */
	DRIVER( firefoxa )	/* 136026           (c) 1984 */
	DRIVER( jedi )		/* 136030           (c) 1984 */

	/* Atari System 1 games */
	DRIVER( atarisy1 )	/* 136033           (c) 1984 */
	DRIVER( peterpak )	/* 136028           (c) 1984 */
	/* Marble Madness */
	DRIVER( marble )	/* 136033           (c) 1984 */
	DRIVER( marble2 )	/* 136033           (c) 1984 */
	DRIVER( marble3 )	/* 136033           (c) 1984 */
	DRIVER( marble4 )	/* 136033           (c) 1984 */
	DRIVER( marble5 )	/* 136033           (c) 1984   (LSI Cartridge) */
	/* Indiana Jones and the Temple of Doom */
	DRIVER( indytemp )	/* 136036           (c) 1985 */
	DRIVER( indytemp2 )	/* 136036           (c) 1985 */
	DRIVER( indytemp3 )	/* 136036           (c) 1985 */
	DRIVER( indytemp4 )	/* 136036           (c) 1985 */
	DRIVER( indytempd )	/* 136036           (c) 1985 */
	DRIVER( indytempc )	/* 136036           (c) 1985 */
	/* Road Runner */
	DRIVER( roadrunn )	/* 136040           (c) 1985 */
	DRIVER( roadrunn2 )	/* 136040           (c) 1985 */
	DRIVER( roadrunn1 )	/* 136040           (c) 1985 */
	/* Road Blasters */
	DRIVER( roadblst )	/* 136048           (c) 1986, 1987 */
	DRIVER( roadblstg )	/* 136048           (c) 1986, 1987 */
	DRIVER( roadblst3 )	/* 136048           (c) 1986, 1987 */
	DRIVER( roadblstg2 )/* 136048           (c) 1986, 1987 */
	DRIVER( roadblst2 )	/* 136048           (c) 1986, 1987 */
	DRIVER( roadblstg1 )/* 136048           (c) 1986, 1987 */
	DRIVER( roadblst1 )	/* 136048           (c) 1986, 1987 */
	DRIVER( roadblstc )	/* 136048           (c) 1986, 1987 */
	DRIVER( roadblstcg )/* 136048           (c) 1986, 1987 */
	DRIVER( roadblstc1 )/* 136048           (c) 1986, 1987 */

	/* Atari System 2 games */
	/* Paperboy */
	DRIVER( paperboy )	/* 136034           (c) 1984 */
	DRIVER( paperboyr2 )/* 136034           (c) 1984 */
	DRIVER( paperboyr1 )/* 136034           (c) 1984 */
	/* Super Sprint */
	DRIVER( ssprint )	/* 136042           (c) 1986 */
	DRIVER( ssprint3 )	/* 136042           (c) 1986 */
	DRIVER( ssprint1 )	/* 136042           (c) 1986 */
	DRIVER( ssprintg )	/* 136042           (c) 1986 */
	DRIVER( ssprintg1 )	/* 136042           (c) 1986 */
	DRIVER( ssprintf )	/* 136042           (c) 1986 */
	DRIVER( ssprints )	/* 136042           (c) 1986 */
	/* Championship Sprint */
	DRIVER( csprint )	/* 136045           (c) 1986 */
	DRIVER( csprint2 )	/* 136045           (c) 1986 */
	DRIVER( csprint1 )	/* 136045           (c) 1986 */
	DRIVER( csprintg )	/* 136045           (c) 1986 */
	DRIVER( csprintg1 )	/* 136045           (c) 1986 */
	DRIVER( csprintf )	/* 136045           (c) 1986 */
	DRIVER( csprints )	/* 136045           (c) 1986 */
	DRIVER( csprints1 )	/* 136045           (c) 1986 */
	/* 720 Degrees */
	DRIVER( 720 )		/* 136047           (c) 1986 */
	DRIVER( 720r3 )		/* 136047           (c) 1986 */
	DRIVER( 720r2 )		/* 136047           (c) 1986 */
	DRIVER( 720r1 )		/* 136047           (c) 1986 */
	DRIVER( 720g )		/* 136047           (c) 1986 */
	DRIVER( 720gr1 )	/* 136047           (c) 1986 */
	/* APB. */
	DRIVER( apb )		/* 136051           (c) 1987 */
	DRIVER( apb6 )		/* 136051           (c) 1987 */
	DRIVER( apb5 )		/* 136051           (c) 1987 */
	DRIVER( apb4 )		/* 136051           (c) 1987 */
	DRIVER( apb3 )		/* 136051           (c) 1987 */
	DRIVER( apb2 )		/* 136051           (c) 1987 */
	DRIVER( apb1 )		/* 136051           (c) 1987 */
	DRIVER( apbg )		/* 136051           (c) 1987 */
	DRIVER( apbf )		/* 136051           (c) 1987 */

	/* Atari polygon games */
	DRIVER( irobot )	/* 136029           (c) 1983 */
	/* Hard Drivin' */
	DRIVER( harddriv )	/* 136052           (c) 1988 */
	DRIVER( harddrivb )	/* 136052           (c) 1988 */
	DRIVER( harddrivg )	/* 136052           (c) 1988 */
	DRIVER( harddrivj )	/* 136052           (c) 1988 */
	DRIVER( harddrivb6 )/* 136052           (c) 1988 */
	DRIVER( harddrivj6 )/* 136052           (c) 1988 */
	DRIVER( harddrivb5 )/* 136052           (c) 1988 */
	DRIVER( harddrivg4 )/* 136052           (c) 1988 */
	DRIVER( harddriv3 )	/* 136052           (c) 1988 */
	DRIVER( harddriv2 )	/* 136052           (c) 1988 */
	DRIVER( harddriv1 )	/* 136052           (c) 1988 */
	/* Hard Drivin' Compact */
	DRIVER( harddrivc )	/* 136068           (c) 1990 */
	DRIVER( harddrivcg )/* 136068           (c) 1990 */
	DRIVER( harddrivcb )/* 136068           (c) 1990 */
	DRIVER( harddrivc1 )/* 136068           (c) 1990 */
	/* Stun Runner */
	DRIVER( stunrun )	/* 136070           (c) 1989 */
	DRIVER( stunrunj )	/* 136070           (c) 1989 */
	DRIVER( stunrun5 )	/* 136070           (c) 1989 */
	DRIVER( stunrune )	/* 136070           (c) 1989 */
	DRIVER( stunrun4 )	/* 136070           (c) 1989 */
	DRIVER( stunrun3 )	/* 136070           (c) 1989 */
	DRIVER( stunrun3e )	/* 136070           (c) 1989 */
	DRIVER( stunrun2 )	/* 136070           (c) 1989 */
	DRIVER( stunrun2e )	/* 136070           (c) 1989 */
	DRIVER( stunrun0 )	/* 136070           (c) 1989 */
	DRIVER( stunrunp )	/* (proto)          (c) 1989 */
	/* Race Drivin' */
	DRIVER( racedriv )	/* 136077           (c) 1990 */
	DRIVER( racedrivb )	/* 136077           (c) 1990 */
	DRIVER( racedrivg )	/* 136077           (c) 1990 */
	DRIVER( racedriv4 )	/* 136077           (c) 1990 */
	DRIVER( racedrivb4 )/* 136077           (c) 1990 */
	DRIVER( racedrivg4 )/* 136077           (c) 1990 */
	DRIVER( racedriv3 )	/* 136077           (c) 1990 */
	DRIVER( racedriv2 )	/* 136077           (c) 1990 */
	DRIVER( racedriv1 )	/* 136077           (c) 1990 */
	DRIVER( racedrivb1 )/* 136077           (c) 1990 */
	DRIVER( racedrivg1 )/* 136077           (c) 1990 */
	/* Race Drivin' Compact */
	DRIVER( racedrivc )		/* 136077           (c) 1990 */
	DRIVER( racedrivcb )	/* 136077           (c) 1990 */
	DRIVER( racedrivcg )	/* 136077           (c) 1990 */
	DRIVER( racedrivc4 )	/* 136077           (c) 1990 */
	DRIVER( racedrivcb4 )	/* 136077           (c) 1990 */
	DRIVER( racedrivcg4 )	/* 136077           (c) 1990 */
	DRIVER( racedrivc2 )	/* 136077           (c) 1990 */
	DRIVER( racedrivc1 )	/* 136077           (c) 1990 */
				/* 136086 - BMX Heat (proto) */
	/* Steel Talons */
	DRIVER( steeltal )	/* 136087           (c) 1990 */
	DRIVER( steeltalg )	/* 136087           (c) 1990 */
	DRIVER( steeltal1 )	/* 136087           (c) 1990 */
	DRIVER( steeltalp )	/* 136087           (c) 1990 */
				/* 136088 - Race Drivin' Panorama */
	/* Street Drivin' */
	DRIVER( strtdriv )	/* 136091 (proto) */
	/* Hard Drivin' Airbourne */
	DRIVER( hdrivair )	/* 136098 (proto) */
	DRIVER( hdrivairp )	/* 136098 (proto) */

	/* later Atari games */

	/* Gauntlet Hardware */
	/* Gauntlet */
	DRIVER( gauntlet )		/* 136037           (c) 1985 */
	DRIVER( gauntlets )		/* 136037           (c) 1985 */
	DRIVER( gauntletj )		/* 136037           (c) 1985 */
	DRIVER( gauntletg )		/* 136037           (c) 1985 */
	DRIVER( gauntletj12 )	/* 136037           (c) 1985 */
	DRIVER( gauntletr9 )	/* 136037           (c) 1985 */
	DRIVER( gauntletgr8 )	/* 136037           (c) 1985 */
	DRIVER( gauntletr7 )	/* 136037           (c) 1985 */
	DRIVER( gauntletgr6 )	/* 136037           (c) 1985 */
	DRIVER( gauntletr5 )	/* 136037           (c) 1985 */
	DRIVER( gauntletr4 )	/* 136037           (c) 1985 */
	DRIVER( gauntletgr3 )	/* 136037           (c) 1985 */
	DRIVER( gauntletr2 )	/* 136037           (c) 1985 */
	DRIVER( gauntletr1 )	/* 136037           (c) 1985 */
	/* Gauntlet - 2 Player */
	DRIVER( gauntlet2p )	/* 136037           (c) 1985 */
	DRIVER( gauntlet2pj )	/* 136037           (c) 1985 */
	DRIVER( gauntlet2pg )	/* 136037           (c) 1985 */
	DRIVER( gauntlet2pr3 )	/* 136037           (c) 1985 */
	DRIVER( gauntlet2pj2 )	/* 136037           (c) 1985 */
	DRIVER( gauntlet2pg1 )	/* 136037           (c) 1985 */
	/* Gauntlet 2 */
	DRIVER( gaunt2 )		/* 136043           (c) 1986 */
	DRIVER( gaunt2g )	/* 136043           (c) 1986 */
	/* Gauntlet 2 - 2 Player */
	DRIVER( gaunt22p )	/* 136043           (c) 1986 */
	DRIVER( gaunt22p1 )	/* 136043           (c) 1986 */
	DRIVER( gaunt22pg )	/* 136043           (c) 1986 */
	/* Vindicators Part II */
	DRIVER( vindctr2 )	/* 136059           (c) 1988 */
	DRIVER( vindctr2r2 )	/* 136059           (c) 1988 */
	DRIVER( vindctr2r1 )	/* 136059           (c) 1988 */

	/* Rare games */
	DRIVER( xtheball )	/* (c) 1991 Rare */
	DRIVER( btoads )	/* (c) 1994 Rare */
	DRIVER( kinst )		/* (c) 1994 Rare */
	DRIVER( kinst14 )	/* (c) 1994 Rare */
	DRIVER( kinst13 )	/* (c) 1994 Rare */
	DRIVER( kinstp )	/* (c) 1994 Rare */
	DRIVER( kinst2 )	/* (c) 1995 Rare */
	DRIVER( kinst2k4 )	/* (c) 1995 Rare */
	DRIVER( kinst213 )	/* (c) 1995 Rare */
	DRIVER( kinst2k3 )	/* (c) 1995 Rare */
	DRIVER( kinst211 )	/* (c) 1995 Rare */
	DRIVER( kinst210 )	/* (c) 1995 Rare */

#endif	/* DRIVER_RECURSIVE */
