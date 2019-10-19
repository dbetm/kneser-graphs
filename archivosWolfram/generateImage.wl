(* ::Package:: *)

myWorkspace = "C:\Users\david\Dropbox\Dev\kneser-graphs\archivosWolfram";
SetDirectory[myWorkspace];

m = Import["matrix.txt", "Table"];
m = Unitize[m];
graph = AdjacencyGraph[m];
pathPhoto = Import["rutaImagen.txt"];
Export[pathPhoto, graph];


(* ::InheritFromParent:: *)
(**)
