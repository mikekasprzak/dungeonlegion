
#include <Rebel/Log.h>
#include <Data/DataBlock.h>

#include <fstream>
#include <string>
#include <String/String.h>
using namespace std;

// TODO: Generate some accessable symbol that contains the size //

int main( int argc, char* argv[] ) {
	if ( argc < 3 ) {
		Log( "Bin2C - Convert a Binary file to a C file\n" );
		Log( "  Usage: Bin2C In.bin Out.c PREFIX SUFFIX\n" );
		return -1;
	}

	// Load File //
	DataBlock* File = new_DataBlock( argv[1] );
	
	string Prefix("");
	string Suffix("");
	
	if ( argc > 3 ) {
		Prefix = argv[3];
	}

	if ( argc > 4 ) {
		Suffix = argv[4];
	}
	
	string BaseName = String::BaseName( String::FileName( String::SystemSlash( argv[1] ) ) );
	string Symbol = Prefix + BaseName + Suffix;
	
	// Open Output File //
	ofstream Out( argv[2] );
	
	Out << "// " << Symbol << " - Generated by Bin2C //" << endl;
	Out << "extern char " << Symbol << "[];" << endl;
	Out << "char " << Symbol << "[] = {";
	
	int NextLine = 0;
	for ( int idx = 0; idx < File->Size; idx++ ) {
		if ( NextLine-- == 0 ) {
			NextLine = 16;
			Out << "\n\t";			
		}
		
		Out << (int)File->Data[idx] << ", ";
	}
	
	Out << endl << "};" << endl;
	
	
	// Close Output File //
	Out.close();
	
	// Done with File //
	delete_DataBlock(File);

	return 0;	
}
