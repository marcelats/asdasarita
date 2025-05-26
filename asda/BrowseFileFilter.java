package asda;
/*
 * Created on 19/09/2003
 *
 */

/**
 * Classe que filtra a visualizao dos arquivos pela sua extensao
 * 
 * @author thais
 * 
 */


/*
 * Copyright (c) 2002 Sun Microsystems, Inc. All  Rights Reserved. 
 */

/*
 * @(#)BrowseFileFilter.java	1.13 02/06/13
 */


import java.io.File;
import java.util.Hashtable;
import java.util.Enumeration;
import javax.swing.*;
import javax.swing.filechooser.*;

 /*
  * @version 1.13 06/13/02 
  * @author Jeff Dinkins
  */
    
public class BrowseFileFilter extends FileFilter {

	private static String TYPE_UNKNOWN = "Tipo desconhecido";
	private static String HIDDEN_FILE = "Arquivo Oculto";

	private Hashtable filters = null;
	private String description = null;
	private String fullDescription = null;
	private boolean useExtensionsInDescription = true;

	/**
	 * Cria um filtro de arquivos.
	 *
	 * @see #addExtension
	 */
	public BrowseFileFilter() {
	this.filters = new Hashtable();
	}

	/**
	 * Cria um filtro de arquivos que aceita um arquivo com uma
	 * dada extens   o.
	 * Examplo: novo BrowseFileFilter("jpg");
	 *
	 * @see #addExtension
	 */
	public BrowseFileFilter(String extension) {
	this(extension,null);
	}

	/**
	 * Cria um filtro de arquivos que aceitam um dado tipo de
	 * arquivos.
	 * Examplo: novo BrowseFileFilter("jpg", "JPEG Image Images");
	 *
	 * Note que o "." antes da extens   o n   o     necess   rio. 
	 * Se fornecido, ele ser    ignorado.
	 *
	 * @see #addExtension
	 */
	public BrowseFileFilter(String extension, String description) {
	this();
	if(extension!=null) addExtension(extension);
	if(description!=null) setDescription(description);
	}

	/**
	 * Cria um filtro de arquivo para um vetor de strings fornecido.
	 * Examplo: novo BrowseFileFilter(String {"gif", "jpg"});
	 *
	 * Note que o "." antes da extens   o n   o     necess   rio. 
	 * Se fornecido, ele ser    ignorado.
	 *
	 * @see #addExtension
	 */
	public BrowseFileFilter(String[] filters) {
	this(filters, null);
	}

	/**
	 * Cria um filtro de arquivo para um vetor de strings e uma descri      o fornecida.
	 * Examplo: novo BrowseFileFilter(String {"gif", "jpg"}, "Gif and JPG Images");
	 *
	 * Note que o "." antes da extens   o n   o     necess   rio. 
	 * Se fornecido, ele ser    ignorado.
	 * 
	 * @see #addExtension
	 */
	public BrowseFileFilter(String[] filters, String description) {
	this();
	for (int i = 0; i < filters.length; i++) {
		// adiciona os filtros um por um
		addExtension(filters[i]);
	}
	if(description!=null) setDescription(description);
	}

	/**
	 *
	 * Arquivos que come   am com "." s   o ignorados.
	 *
	 * @see #getExtension
	 * @see FileFilter#accepts
	 */
	public boolean accept(File f) {
	if(f != null) {
		if(f.isDirectory()) {
		return true;
		}
		String extension = getExtension(f);
		if(extension != null && filters.get(getExtension(f)) != null) {
		return true;
		};
	}
	return false;
	}

	/**
	 * Retorna a extens   o do arquivo.
	 *
	 * @see #getExtension
	 * @see FileFilter#accept
	 */
	 public String getExtension(File f) {
	if(f != null) {
		String filename = f.getName();
		int i = filename.lastIndexOf('.');
		if(i>0 && i<filename.length()-1) {
		return filename.substring(i+1).toLowerCase();
		};
	}
	return null;
	}

	/**
	 * 
	 */
	public void addExtension(String extension) {
	if(filters == null) {
		filters = new Hashtable(5);
	}
	filters.put(extension.toLowerCase(), this);
	fullDescription = null;
	}


	/**
	 * Retorna a descri      o humana dos arquivos 
	 * Examplo: "JPEG e GIF Arquivos de Imagem (*.jpg, *.gif)"
	 *
	 * @see setDescription
	 * @see setExtensionListInDescription
	 * @see isExtensionListInDescription
	 * @see FileFilter#getDescription
	 */
	public String getDescription() {
	if(fullDescription == null) {
		if(description == null || isExtensionListInDescription()) {
		fullDescription = description==null ? "(" : description + " (";
		// build the description from the extension list
		Enumeration extensions = filters.keys();
		if(extensions != null) {
			fullDescription += "." + (String) extensions.nextElement();
			while (extensions.hasMoreElements()) {
			fullDescription += ", ." + (String) extensions.nextElement();
			}
		}
		fullDescription += ")";
		} else {
		fullDescription = description;
		}
	}
	return fullDescription;
	}

	/**
	 * Seta a descri      o humana para o filtro de arquivos. 
	 * Examplo: filter.setDescription("Gif e JPG Imagens");
	 *
	 * @see setDescription
	 * @see setExtensionListInDescription
	 * @see isExtensionListInDescription
	 */
	public void setDescription(String description) {
	this.description = description;
	fullDescription = null;
	}

	/**
	 * Determina se a lista de extens   o tem uma descri      o humana (.jpg, .gif, etc).
	 *
	 * Relevante somente se descri      o foi provida pelo construtor ou usando
	 * setDescription();
	 *
	 * @see getDescription
	 * @see setDescription
	 * @see isExtensionListInDescription
	 */
	public void setExtensionListInDescription(boolean b) {
	useExtensionsInDescription = b;
	fullDescription = null;
	}

	/**
	 * Retorna se a lista de extens   es (.jpg, .gif, etc) possui
	 * uma descri      o humana.
	 *
	 * Relevante somente se descri      o foi provida pelo construtor ou usando
	 * setDescription();
	 *
	 * @see getDescription
	 * @see setDescription
	 * @see setExtensionListInDescription
	 */
	public boolean isExtensionListInDescription() {
	return useExtensionsInDescription;
	}
}




