/****************************************************************************
**
** nifscope: a tool for analyzing and editing NetImmerse files (.nif & .kf)
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/


#ifdef QT_OPENGL_LIB

#include "glview.h"

#include <QtOpenGL>

#include <math.h>

#include "nifmodel.h"


/* XPM */
static char * click_xpm[] = {
"256 32 43 1",
" 	c None",
".	c #1B130F","+	c #361609","@	c #452215","#	c #362B25","$	c #402919",
"%	c #51240F","&	c #752B13","*	c #623922","=	c #4C423D","-	c #70381A",
";	c #95381D",">	c #924424",",	c #AA3C1A","'	c #A34119",")	c #9A471C",
"!	c #655A54","~	c #7F523B","{	c #8B502B","]	c #BE5121","^	c #C84D1E",
"/	c #B45C2D","(	c #7B726C","_	c #AC6935",":	c #AD6644","<	c #A1714E",
"[	c #D4642B","}	c #CA6A29","|	c #9C7864","1	c #C76C3A","2	c #E46227",
"3	c #908782","4	c #E77231","5	c #BF8849","6	c #CC8344","7	c #DF8045",
"8	c #D98A3A","9	c #BB926A","0	c #E6863A","a	c #B1A299","b	c #BD9F8A",
"c	c #E79E50","d	c #E0B560",
"                                                                                                                                                                                                                                                                ",
"                                                                                                                                                                                                                                                                ",
"                                                                                                                                                                                                                                                                ",
"                                                                                                                                                                                                                                                                ",
"                                                                                                                                                                                                                                                                ",
"                 b9dd9                        a/,;|         b:75|                                  |/,;|                  9c6:b                                                                               9dd9a                                             ",
"                 <cdd63                       :2;,&a        6[40{a                                 ]24^>a b9b            a7007|                                                                              b7ddc~                                             ",
"                 70dc6=                      b1[''&=       b71/8{(                                |,][})|ccc7~           |7776*a                  :/1|                                                       <0ddc*               a<6:|                         ",
"                 68dd_$                      b0}1})!       b8//c{!                                |1'/}}{8c01*a          |7711*3                 :4[41a                                                      :ccd6*               :44[>                         ",
"                 6c5c6$                      |88}8_!       9}]/8{!                                |}]}0}{100]@3          |11/1-3                 70[4}!                                                      <c55c*               6[17/(                        ",
"              abbcc566#     bab     b      bb|]'/]'*bbb    |8/'}<!    aaba                  bba   |]]']>${}0>#     abb   <1:11*3               b|2];)]>b      bba               a      a    ba bbb         bb6cc57*      aba     |7[>),{b      bbb              ",
"            9d72cc_:5/$  b5c7c71| b171:   1[4}2')]]^44[/:  |0/)8{!  b677c769              91442[1a<[]']>*_80:$   95c77:< 9761/-3a171:         1422-@-']^19  1cdcc5|           b6[1<  b1[[1:}42}422}:    bd640d8{5_*   b5c0c4:9a174[-@%/^^[| b1}2221/b           ",
"           500>/6_**5_$ |cc77:111|124[)3 |^[[[2'%&)'[],]^>a|0))7{! 9c07:1607<            <2[]]]^2]/[]'^'{700>*  94d611776_71/1>|}2[[)(       b22]&+=#&;]}_9/17811c6<          17^4{a :^^[422[,']]}[^{  9001)1_-$<6*  5cc71:1171241&.==%'1[><[2[[}]]^'|          ",
"          :00{#%*..(56~971{$**$>:1:];';$ :^,,,,;#$+$%%$;][_<0>>8)!5dc~$*@$*7/(          b^]%+@+%,]>']']]]4}0>-3:01~$~@~1/<11:/:16-%>&#       ~,,'>= a{^^}}c1>$$*$<65|        a17>;&! ;]/,,,&...$%@&],:|70_$@*$#=<6{a17/~#**@~171,;&= a>,,,,^^;@%%@%;]-          ",
"         b2/_)>1c5<386567;{<71:~:11,>/;# &,;&,';=3]][^]';]/80>/8}_7d{<571:~>/*          ;,&#]^^^,'%'^,^,]]6};)|c0-~dd_11;~/11161~@~]%!       (;;,^'|:22])8}>-558_<_c*        |11;;>! ,,;;;;&!<,]^/>;]^[[_)>185_a585<7/%{:71:~::;;/];|:^,;&;^&&>^^]-&'&3         ",
"         >^-{}//d}6<c_:1:-:7777::11]]1'$ >]''^^'-[4^]']]&;){)'_d{_0{~711[>!1_$         |2,-]2]'''))[^']]]'6/>_d0{~d8:/:>{<71{:1~@:4>.3        +.%]2]^^&+%_)%_d8175{6*3       3:/]]{= /]',^^;~22]^2'-,^^&{/1/58/<56{11><7777161{@+%/]/[2&+%);&>2^4]-{]%(         ",
"         /^%{]%.#)__c-~_{~}{$-1~:71;;>;# &,;'],,;^'...-]->;${/}c*~_*{}6:_-<0{#         {,%&,&.....%}^]^]],/'/-5}*_c-.....~7{$*@$:^&.(          3=>][2]+==/>~06$*{__}<(       31:;;-! ;;;;,,,;,&.@)'/2^]&~]-.#-/_8_*5{*11-*1171:#(=&/,,;.=*,&*,^)]&~^^+3         ",
"         ;,)1}.3a)6/0{(5:_0%!~111111;;;# >';'']''^&#  -';,)={]8c$<_$:65_-6c7*!         ;]&>,#! 3(3~]]]],,]1})$51*{}$3 3(3<7{!!=(11&!             )]]]'# ~}}{8-=(_}70<!       |:1/'&= ;]','';]^-!(]/]^],)_4%( {1_0/=9_~8-#!::6:>= a;,,''# ~'-!'')>)[2>.          ",
"         ',)1[*  11_}{(6_)7*a<7~>:,;&;;@a,,&;]]]'^)!  /]-;]*_}}5$|_$!*~_[748{3        a;,&&,-a|[24/[']]''}}]_$51{_8~a9646_7_(574>,;-             '}']'+ <}]{0{3<6{{6*!       3>;&;;~a,,&;,//,^&(|^))]],)/[-a :1_}_!{6/7{!b7]:/>#  ;;;;;. {]&!%&)]22]'~          ",
"         >'-{})99[{{6_|6{~/_9c7*{1/;%&,;;,;&']]')'];:/2'->}-1}}8$<7$b<8c7}1cc/a        &;%&]]^222^)']']],}'}_~5/*:8c6cc71{_6:c71[;;;~            )^,''$ ~/)*88_18-<_$(       a{:@&;;;^&&;]^'']]>]2&*]]]>*}1<97)~_8!_6*_}<90:{>/#  &,;;;# {,&(<]22^]]^'~         ",
"         -;_{)1001**5_<c_~/_cc{:11/,&~;',,&@&^,;%&&;,,;&>,0>}18}{58<90c71//67_!        &;;>;;],''&@&;',''0'}/_8/{6_566_/)~57c71:1&&;;|           &;,;;# |>/~}_17__58#3       a{1*;;;,;%%;,'&%),];&%>,''/~_)007-${6~c_~)1cc7*={_@  ;,,,;$ ~''~^^;;,;>';*         ",
"         *)1{~-/{%#(8_556}~{:{~<7**>[1%...@~,,,;*$@&;%@>2]@*/)4/{_60555_)-$:8*!        !>['&+.%;,;-,,^');1//)){)0_{$.<_8>~7671~@{/{1[-a          ;,,,'$  -/>~-){*<d-#         ~/[1$..+%~^,,&=@&;&@~^;%-}>~-_)-$!55_d60{{__*$(:/*a )^[^)# 3&,,>;;;&@-,)$         ",
"         3%)}/>--_95d5$*5}/16557>.=@///::>,^^]',;:,,,;;^'@.!-)[)%$*6c_5~*/_c_$(        a@&,^>>,^&++&,,;%@)}/)%=*<6c5<dd{%*ccc:@!@:[][-(          &,,;&#  *-)}/6_5d5.3         (%>]>::/,^^,'&!~;,;;^;+##>}/>{*_<5cd*~511/:_5_:7/@3 >}',&#  @&,,'%%&;,,%#         ",
"          (+&]]]^[][}%=($-/41}1-.! !+-)/[,1);%&&,;^^,/]>+.a @&>%.3=%>]}0}27{$#          3.@&;,;%.#(@-&%.=%>;-.3!#%_/]_*.=!>1]>.a!-//_@(          -)')%=  a$%',}/]-$#           =@-/111'/)&;&~]^,],;.# 3+-'^^^[]}}{.!${]4}}41[7_#3 ~>/>+!  3+%;,][^},%.(         ",
"           (.++&%&%%+.3 a..%%%..(   3#..........+.+%*+..=   3...3  !..---%+.=             !.....3  3...3 #...=   =....#3  @%%.=  =+@$.           !@*$.a    #.+%%..!             (........+&;;^;%@..=    ..+%&%%%%.! 3..%-%+.+@.#  !%*+.     ..+---$..a          ",
"             !###====3    3===(        333     3!(!!=!(              (=###!                  a            33a      aa     3=#=    =#=3            !##3      3===!                  33a   *,;;,%#=(       (=###===(    (=#=!3!=!    !#=3      3==#==3            ",
"                                                                                                                                                                                         ~;,;;@(                                                                ",
"                                                                                                                                                                                         ~&,;;+3                                                                ",
"                                                                                                                                                                                         (&;;&.                                                                 ",
"                                                                                                                                                                                          +...=                                                                 ",
"                                                                                                                                                                                           (!3                                                                  ",
"                                                                                                                                                                                                                                                                "};

GLView::GLView()
	: QGLWidget()
{
	nif = 0;
	xRot = yRot = zRot = 0;
	zoom = 1000;
	zInc = 1;
	
	updated = false;
	doCompile = doCenter = false;
	
	lightsOn = true;
	drawaxis = true;
	
	model = 0;

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(advanceGears()));
}

GLView::~GLView()
{
	makeCurrent();
	glDeleteLists(nif, 1);
	flushTextureCache();
}

void GLView::setNif( NifModel * nif )
{
	if ( model )
	{
		disconnect( model, SIGNAL( dataChanged( const QModelIndex & , const QModelIndex & ) ),
			this, SLOT( dataChanged() ) );
		updated = true;
	}
	model = nif;
	if ( model )
	{
		connect( model, SIGNAL( dataChanged( const QModelIndex & , const QModelIndex & ) ),
			this, SLOT( dataChanged() ) );
	}
}

void GLView::setTextureFolder( const QString & tf )
{
	texfolder = tf;
	updated = true;
}

void GLView::setLighting( bool l )
{
	lightsOn = l;
	updateGL();
}

void GLView::setDrawAxis( bool a )
{
	drawaxis = a;
	updateGL();
}

void GLView::setRotate( bool r )
{
	if ( r )
		timer->start(25);
	else
		timer->stop();
}

void GLView::setXRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void GLView::setYRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void GLView::setZRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void GLView::setXTrans( int x )
{
	if ( x != xTrans )
	{
		xTrans = x;
		updateGL();
	}
}

void GLView::setYTrans( int y )
{
	if ( y != yTrans )
	{
		yTrans = y;
		updateGL();
	}
}

void GLView::setZoom( int z )
{
	if ( z <= 10 || z >= 100000 )
		return;
	if ( z != zoom )
	{
		zoom = z;
		emit zoomChanged( zoom );
		updateGL();
	}
}

void GLView::advanceGears()
{
	setZRotation( zRot + zInc );
	updateGL();
}

void GLView::dataChanged()
{
	updated = true;
	updateGL();
}

void GLView::compile( bool center )
{
	doCompile = true;
	doCenter = center;
	updateGL();
}

void GLView::initializeGL()
{
	QString extensions( (const char *) glGetString(GL_EXTENSIONS) );
	//qDebug( (const char *) glGetString(GL_EXTENSIONS) );

	qglClearColor( palette().color( QPalette::Active, QPalette::Background ) );

	static const GLfloat L0position[4] = { 5.0f, 5.0f, 10.0f, 1.0f };
	static const GLfloat L0ambient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
	static const GLfloat L0diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv( GL_LIGHT0, GL_POSITION, L0position );
	glLightfv( GL_LIGHT0, GL_AMBIENT, L0ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, L0diffuse );
	glEnable( GL_LIGHT0 );
	
	glShadeModel( GL_SMOOTH );
}

void GLView::paintGL()
{
	if ( ! isVisible() )
		return;
	
	makeCurrent();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int x = qMax( width(), height() );
	
	float fx = (float) width() / x;
	float fy = (float) height() / x;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-fx, +fx, -fy, fy, 5.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if ( lightsOn )
		glEnable( GL_LIGHTING );
	else
		glDisable( GL_LIGHTING );
	
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_NORMALIZE );
	glEnable( GL_CULL_FACE );
	glEnable( GL_TEXTURE_2D );

	if ( doCompile )
	{
		doCompile = false;
		updated = false;
		
		if ( ! nif )	nif = glGenLists( 1 );
		glNewList( nif, GL_COMPILE );
		
		nodestack.clear();
		worldtrans.clear();
		
		if ( doCenter )
		{
			boundMin = Vector( +1000000000, +1000000000, +1000000000 );
			boundMax = Vector( -1000000000, -1000000000, -1000000000 );
		}
		
		if ( model )
		{
			glDisable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			for ( int r = 1; r < model->rowCount( QModelIndex() ); r++ )
			{
				if ( model->inherits( model->itemName( model->index( r, 0 ) ), "AParentNode" ) )
				{
					// first pass: only opaque objects
					glDepthMask( GL_TRUE );
					glDisable( GL_BLEND );
					if ( compileNode( r-1, false ) )
					{
						// second pass: only alpha enabled objects
						glDepthMask( GL_FALSE );
						glEnable( GL_BLEND );
						compileNode( r-1, true );
					}
					break;
				}
			}
			glDepthMask( GL_TRUE );
			glDisable( GL_BLEND );
		}
		glEndList();
	}
	
	if ( doCenter )
	{
		doCenter = false;
		double max = 0;
		for ( int c = 0; c < 3; c++ )
			max = qMax( max, qMax( fabs( boundMin[ c ] ), fabs( boundMax[ c ] ) ) );
		zoom = (int) ( max * 40 );
		xTrans = 0;
		yTrans = (int) ( boundMin[3] - boundMax[3] ) * 20;
		xRot = - 90*16;
		yRot = 0;
	}
	
	glLoadIdentity();
	glTranslated( xTrans / 20.0, - yTrans / 20.0, - zoom / 10.0);
	glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
	
	if ( nif ) glCallList(nif);
	
	glDisable( GL_LIGHTING );
	glDisable( GL_TEXTURE_2D );

	if ( drawaxis )
	{
		glBegin( GL_LINES );
		glColor3f( 1.0, 0.0, 0.0 );
		glVertex3f( - 1000.0, 0, 0 );
		glVertex3f( + 1000.0, 0, 0 );
		glVertex3f( + 1000.0,    0,    0 );
		glVertex3f( +  950.0, + 20,    0 );
		glVertex3f( + 1000.0,    0,    0 );
		glVertex3f( +  950.0, - 20,    0 );
		glVertex3f( + 1000.0,    0,    0 );
		glVertex3f( +  950.0,    0, + 20 );
		glVertex3f( + 1000.0,    0,    0 );
		glVertex3f( +  950.0,    0, - 20 );
		glColor3f( 0.0, 1.0, 0.0 );
		glVertex3f( 0, - 1000.0, 0 );
		glVertex3f( 0, + 1000.0, 0 );
		glVertex3f(    0, + 1000.0,    0 );
		glVertex3f( + 20, +  950.0,    0 );
		glVertex3f(    0, + 1000.0,    0 );
		glVertex3f( - 20, +  950.0,    0 );
		glVertex3f(    0, + 1000.0,    0 );
		glVertex3f(    0, +  950.0, + 20 );
		glVertex3f(    0, + 1000.0,    0 );
		glVertex3f(    0, +  950.0, - 20 );
		glColor3f( 0.0, 0.0, 1.0 );
		glVertex3f( 0, 0, - 1000.0 );
		glVertex3f( 0, 0, + 1000.0 );
		glVertex3f(    0,    0, + 1000.0 );
		glVertex3f(    0, + 20, +  950.0 );
		glVertex3f(    0,    0, + 1000.0 );
		glVertex3f(    0, - 20, +  950.0 );
		glVertex3f(    0,    0, + 1000.0 );
		glVertex3f( + 20,    0, +  950.0 );
		glVertex3f(    0,    0, + 1000.0 );
		glVertex3f( - 20,    0, +  950.0 );
		glEnd();
		
		glColor3f( 1.0, 0.0, 1.0 );
		glBegin( GL_LINE_STRIP );
		glVertex3f( boundMin[0], boundMin[1], boundMin[2] );
		glVertex3f( boundMin[0], boundMax[1], boundMin[2] );
		glVertex3f( boundMin[0], boundMax[1], boundMax[2] );
		glVertex3f( boundMin[0], boundMin[1], boundMax[2] );
		glVertex3f( boundMin[0], boundMin[1], boundMin[2] );
		glEnd();
		glBegin( GL_LINE_STRIP );
		glVertex3f( boundMax[0], boundMin[1], boundMin[2] );
		glVertex3f( boundMax[0], boundMax[1], boundMin[2] );
		glVertex3f( boundMax[0], boundMax[1], boundMax[2] );
		glVertex3f( boundMax[0], boundMin[1], boundMax[2] );
		glVertex3f( boundMax[0], boundMin[1], boundMin[2] );
		glEnd();
		glBegin( GL_LINES );
		glVertex3f( boundMin[0], boundMin[1], boundMin[2] );
		glVertex3f( boundMax[0], boundMin[1], boundMin[2] );
		glVertex3f( boundMin[0], boundMax[1], boundMin[2] );
		glVertex3f( boundMax[0], boundMax[1], boundMin[2] );
		glVertex3f( boundMin[0], boundMax[1], boundMax[2] );
		glVertex3f( boundMax[0], boundMax[1], boundMax[2] );
		glVertex3f( boundMin[0], boundMin[1], boundMax[2] );
		glVertex3f( boundMax[0], boundMin[1], boundMax[2] );
		glEnd();
	}
	
	glDisable( GL_DEPTH_TEST );

	glLoadIdentity();
	if ( updated )
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho (0.0, width(), 0.0, height(), -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable( GL_TEXTURE_2D );
		if ( ! click_tex )
			click_tex = bindTexture( QImage( click_xpm ) );
		else
			glBindTexture( GL_TEXTURE_2D, click_tex );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
		glColor4f( 0.5, 0.5, 0.5, 1.0 );
		glBegin( GL_QUADS );
		glTexCoord2d( 0.0, 0.0 );		glVertex2d( 0.0, 0.0 );
		glTexCoord2d( 1.0, 0.0 );		glVertex2d( 255.0, 0.0 );
		glTexCoord2d( 1.0, 1.0 );		glVertex2d( 255.0, 31.0 );
		glTexCoord2d( 0.0, 1.0 );		glVertex2d( 0.0, 31.0 );
		glEnd();
	}
	
	GLenum err;
	while ( ( err = glGetError() ) != GL_NO_ERROR )
		qDebug() << "GL ERROR : " << (const char *) gluErrorString( err );
}

void GLView::resizeGL(int width, int height)
{
	makeCurrent();
	glViewport(0, 0, width, height);
}

bool GLView::compileNode( int blockNumber, bool alphatoggle )
{
	bool has_alpha = false;
	
	QModelIndex idx = model->getBlock( blockNumber );
	if ( !idx.isValid() ) return has_alpha;
	
	if ( ( model->getInt( idx, "flags" ) & 1 ) != 0 )	return has_alpha;
	
	if ( nodestack.contains( blockNumber ) )
	{
		qWarning( "infinite recursive node construct detected ( %d -> %d )", nodestack.top(), blockNumber );
		return has_alpha;
	}
	
	QString idnt;
	while ( idnt.length() < nodestack.count()*2 )
		idnt += "  ";
	
	//qDebug() << idnt << "compile " << model->itemName( idx ) << " (" << blockNumber << ") " << model->itemValue( model->getIndex( idx, "name" ) ).toString();

	nodestack.push( blockNumber );
	matrixstack.push( Matrix( model, idx ) );
	
	Matrix matrix;
	foreach ( Matrix m, matrixstack )
		matrix = matrix * m;
	worldtrans[blockNumber] = matrix;

	QModelIndex children = model->getIndex( idx, "children" );
	QModelIndex childlinks = model->getIndex( children, "indices" );
	if ( ! ( children.isValid() && childlinks.isValid() ) )
	{
		qWarning() << "compileNode( " << blockNumber << " ) : children link list not found";
		return has_alpha;
	}
	for ( int c = 0; c < model->rowCount( childlinks ); c++ )
	{
		int r = model->itemValue( childlinks.child( c, 0 ) ).toInt();
		QModelIndex child = model->getBlock( r );
		if ( ! child.isValid() )
		{
			qWarning() << "block " << r << " not found";
			continue;
		}
		if ( model->inherits( model->itemName( child ), "AParentNode" ) )
		{
			has_alpha |= compileNode( r, alphatoggle );
		}
		else if ( model->itemName( child ) == "NiTriShape" || model->itemName( child ) == "NiTriStrips" )
		{
			//qDebug() << idnt << "   compile " << model->itemName( child ) << " (" << r << ")";
			
			if ( model->getInt( child, "flags" ) & 1 )
			{
				//qDebug() << "      shape is hidden";
				continue;
			}
			
			QString	tex_file;
			int		tex_set = 0;
			GLenum	tex_filter = GL_LINEAR;
			
			bool tri_alpha = false;
			
			QModelIndex properties = model->getIndex( child, "properties" );
			QModelIndex proplinks = model->getIndex( properties, "indices" );
			for ( int p = 0; p < model->rowCount( proplinks ); p++ )
			{
				int prop = model->itemValue( proplinks.child( p, 0 ) ).toInt();
				
				QModelIndex property = model->getBlock( prop );
				QString propname = model->itemName( property );
				if ( propname == "NiMaterialProperty" )
				{
					QColor ambient = model->getValue( property, "ambient color" ).value<QColor>();
					QColor diffuse = model->getValue( property, "diffuse color" ).value<QColor>();
					QColor specular = model->getValue( property, "specular color" ).value<QColor>();
					
					GLfloat shininess = model->getFloat( property, "glossiness" ) * 1.28; // range 0 ~ 128 (nif 0~100)
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
					GLfloat alpha = model->getFloat( property, "alpha" );
					
					GLfloat ambientColor[4] = { ambient.redF(), ambient.greenF(), ambient.blueF() , alpha };
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientColor);
					GLfloat diffuseColor[4] = { diffuse.redF(), diffuse.greenF(), diffuse.blueF() , alpha };
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);
					GLfloat specularColor[4] = { specular.redF(), specular.greenF(), specular.blueF() , alpha };
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);
					
					glColor4f( diffuse.redF(), diffuse.greenF(), diffuse.blueF(), alpha );
				}
				else if ( propname == "NiTexturingProperty" )
				{
					QModelIndex basetex = model->getIndex( property, "base texture" );
					QModelIndex basetexdata = model->getIndex( basetex, "texture data" );
					int src = model->getInt( basetexdata, "source" );
					QModelIndex sourcetexture = model->getBlock( src, "NiSourceTexture" );
					if ( sourcetexture.isValid() )
					{
						QModelIndex source = model->getIndex( sourcetexture, "texture source" );
						tex_file = model->getValue( source, "file name" ).toString();
					}
					switch ( model->getInt( basetexdata, "filter mode" ) )
					{
						case 0:		tex_filter = GL_NEAREST;	break;
						case 1:		tex_filter = GL_LINEAR;		break;
						default:
							tex_filter = GL_NEAREST;
							break;
						/*
						case 2:		tex_filter = GL_NEAREST_MIPMAP_NEAREST;		break;
						case 3:		tex_filter = GL_LINEAR_MIPMAP_NEAREST;		break;
						case 4:		tex_filter = GL_NEAREST_MIPMAP_LINEAR;		break;
						case 5:		tex_filter = GL_LINEAR_MIPMAP_LINEAR;		break;
						*/
					}
					tex_set = model->getInt( basetexdata, "texture set" );
				}
				else if ( propname == "NiAlphaProperty" )
				{
					tri_alpha = true;
					has_alpha = true;
					// default blend function
					glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				}
			}
			
			int data = model->getInt( child, "data" );
			QModelIndex tridata = model->getBlock( data );
			if ( alphatoggle != tri_alpha )
				continue;
			if ( ! tridata.isValid() )
			{
				qWarning() << model->itemName( child ) << "(" << r << ") data block (" << data << ") not found";
				continue;
			}
			if ( model->itemName( tridata ) != "NiTriShapeData" && model->itemName( tridata ) != "NiTriStripsData" )
			{
				qWarning() << model->itemName( child ) << "(" << r << ") data block (" << data << ") type mismatch";
				continue;
			}
			QModelIndex vertices = model->getIndex( tridata, "vertices" );
			if ( ! vertices.isValid() )
			{
				qWarning() << model->itemName( tridata ) << "(" << data << ") contains no vertices";
				continue;
			}
			QVector<Vector> verts;
			for ( int r = 0; r < model->rowCount( vertices ); r++ )
			{
				verts.append( Vector( model, model->index( r, 0, vertices ) ) );
			}
			QModelIndex normals = model->getIndex( tridata, "normals" );
			QVector<Vector> norms;
			if ( normals.isValid() )
			{
				for ( int r = 0; r < model->rowCount( normals ); r++ )
					norms.append( Vector( model, model->index( r, 0, normals ) ) );
			}
			QModelIndex vertexcolors = model->getIndex( tridata, "vertex colors" );
			QVector<QColor> colors;
			if ( vertexcolors.isValid() )
			{
				for ( int r = 0; r < model->rowCount( vertexcolors ); r++ )
					colors.append( model->itemValue( vertexcolors.child( r, 0 ) ).value<QColor>() );
			}
			QVector<GLfloat> uvs;
			if ( ! tex_file.isEmpty()  )
			{
				GLuint tex_id = compileTexture( tex_file );
				if ( tex_id != 0 )
				{
					glBindTexture( GL_TEXTURE_2D, tex_id );
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex_filter );
					glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
					
					QModelIndex uvcoord = model->getIndex( tridata, "uv sets" );
					QModelIndex uvcoordset = model->index( tex_set, 0, uvcoord );
					if ( uvcoord.isValid() && uvcoordset.isValid() )
					{
						for ( int r = 0; r < model->rowCount( uvcoordset ); r++ )
						{
							QModelIndex uv = model->index( r, 0, uvcoordset );
							uvs.append( model->getFloat( uv, "u" ) );
							uvs.append( model->getFloat( uv, "v" ) );
						}
					}
				}
			}
			
			int skin = model->getInt( child, "skin instance" );
			QModelIndex skininst = model->getBlock( skin, "NiSkinInstance" );
			QModelIndex skindata;
			if ( skininst.isValid() )
			{
				int sdat = model->getInt( skininst, "data" );
				skindata = model->getBlock( sdat, "NiSkinData" );
			}
			
			glPushMatrix();
			if ( skininst.isValid() && skindata.isValid() )
			{
				QVector<int> bones;
				QModelIndex idxBones = model->getIndex( model->getIndex( skininst, "bones" ), "bones" );
				for ( int b = 0; b < model->rowCount( idxBones ); b++ )
					bones.append( model->itemValue( model->index( b, 0, idxBones ) ).toInt() );
				idxBones = model->getIndex( skindata, "bone list" );
				if ( idxBones.isValid() )
				{
					QVector<Vector> wverts( verts.count() );
					
					for ( int b = 0; b < model->rowCount( idxBones ) && b < bones.count(); b++ )
					{
						Matrix m1 = worldtrans.value( bones.value( b ) ) * Matrix( model, model->index( b, 0, idxBones ) );
						QModelIndex idxWeights = model->getIndex( model->index( b, 0, idxBones ), "vertex weights" );
						if ( idxWeights.isValid() )
						{
							for ( int w = 0; w < model->rowCount( idxWeights ); w++ )
							{
								int v = model->getInt( model->index( w, 0, idxWeights ), "index" );
								wverts[ v ] += m1 * verts.value( v ) * model->getFloat( model->index( w, 0, idxWeights ), "weight" );
							}
						}
						else
							qDebug() << "weight list not found";
					}
					
					verts = wverts;
					
					if ( doCenter )
					{
						foreach ( Vector v, verts )
						{
							for ( int i = 0; i < 3; i++ )
							{
								if ( v[i] < boundMin[i] )	boundMin[i] = v[i];
								if ( v[i] > boundMax[i] )	boundMax[i] = v[i];
							}
						}
					}
					
				}
				else
					qDebug() << "bone list not found";
			}
			else
			{
				Matrix m1 = worldtrans.value( nodestack.top() ) * Matrix( model, child );
				
				if ( doCenter )
				{
					foreach ( Vector v, verts )
					{
						Vector w = m1 * v;
						for ( int i = 0; i < 3; i++ )
						{
							if ( w[i] < boundMin[i] )	boundMin[i] = w[i];
							if ( w[i] > boundMax[i] )	boundMax[i] = w[i];
						}
					}
				}
				
				m1.glMultMatrix();
			}
			
			if ( model->itemName( tridata ) == "NiTriShapeData" )
			{
				glBegin( GL_TRIANGLES );
				QModelIndex triangles = model->getIndex( tridata, "triangles" );
				if ( triangles.isValid() )
				{
					for ( int r = 0; r < model->rowCount( triangles ); r++ )
					{
						QModelIndex triangle = model->index( r, 0, triangles );
						int v1 = model->getInt( triangle, "v1" );
						int v2 = model->getInt( triangle, "v2" );
						int v3 = model->getInt( triangle, "v3" );
						if ( verts.count() > v1 && verts.count() > v2 && verts.count() > v3 )
						{
							if ( norms.count() > v1 ) norms[v1].glNormal();
							if ( uvs.count() > v1*2 ) glTexCoord2f( uvs[v1*2+0], uvs[v1*2+1] );
							if ( colors.count() > v1 ) { QColor c = colors[v1]; glColor4f( c.redF(), c.greenF(), c.blueF(), c.alphaF() ); }
							verts[v1].glVertex();
							if ( norms.count() > v2 ) norms[v2].glNormal();
							if ( uvs.count() > v2*2 ) glTexCoord2f( uvs[v2*2+0], uvs[v2*2+1] );
							if ( colors.count() > v2 ) { QColor c = colors[v2]; glColor4f( c.redF(), c.greenF(), c.blueF(), c.alphaF() ); }
							verts[v2].glVertex();
							if ( norms.count() > v3 ) norms[v3].glNormal();
							if ( uvs.count() > v3*2 ) glTexCoord2f( uvs[v3*2+0], uvs[v3*2+1] );
							if ( colors.count() > v3 ) { QColor c = colors[v3]; glColor4f( c.redF(), c.greenF(), c.blueF(), c.alphaF() ); }
							verts[v3].glVertex();
						}
					}
				}
				else
					qWarning() << model->itemName( tridata ) << "(" << data << ") triangle array not found";
				glEnd();
			}
			else
			{
				QModelIndex points = model->getIndex( tridata, "points" );
				if ( points.isValid() )
				{
					for ( int r = 0; r < model->rowCount( points ); r++ )
					{
						glBegin( GL_TRIANGLE_STRIP );
						QModelIndex strip = points.child( r, 0 );
						for ( int s = 0; s < model->rowCount( strip ); s++ )
						{
							int v1 = model->itemValue( strip.child( s, 0 ) ).toInt();
							if ( norms.count() > v1 ) norms[v1].glNormal();
							if ( uvs.count() > v1*2 ) glTexCoord2f( uvs[v1*2+0], uvs[v1*2+1] );
							if ( colors.count() > v1 ) { QColor c = colors[v1]; glColor4f( c.redF(), c.greenF(), c.blueF(), c.alphaF() ); }
							verts[v1].glVertex();
						}
						glEnd();
					}
				}
				else
					qWarning() << model->itemName( tridata ) << "(" << data << ") 'points' array not found";
			}
			glPopMatrix();
		}
	}

	matrixstack.pop();
	nodestack.pop();

	GLenum err;
	while ( ( err = glGetError() ) != GL_NO_ERROR )
		qDebug() << "GL ERROR : " << (const char *) gluErrorString( err );
	return has_alpha;
}

void GLView::normalizeAngle(int *angle)
{
	while (*angle < 0)
		*angle += 360 * 16;
	while (*angle > 360 * 16)
		*angle -= 360 * 16;
}

void GLView::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void GLView::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton)
	{
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton)
	{
		setZoom( zoom + 8 * dy );
		setZRotation(zRot + 8 * dx);
	}
	else if ( event->buttons() & Qt::MidButton)
	{
		setXTrans( xTrans + dx * 5 );
		setYTrans( yTrans + dy * 5 );
	}
	lastPos = event->pos();
}

void GLView::mouseDoubleClickEvent( QMouseEvent * )
{
	compile( false );
}

void GLView::wheelEvent( QWheelEvent * event )
{
	if ( event->delta() > 0 )
	{
		setZoom( zoom + zoom / 8 );
	}
	else if ( event->delta() < 0 )
	{
		setZoom( zoom - zoom / 8 );
	}
}



#endif
