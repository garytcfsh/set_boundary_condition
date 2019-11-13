# set_boundary_condition

> This is a program that helps Fracman users to set boundary conditions of irregular shape more easily by using QGIS.

----
## Step1: Set boundary conditions
1. This will generate a csv file when you click "generate QGIS import file" button and select a mff file which was created by "Create Mesh" in Fracman.
2. In QGIS, add a csv layer by "Layer->Add Layer->Add Delimited Text Layer...".
3. In QGIS | Data Source Manager | Delimited Text, selecte the csv file which was generated in step 1-1. Click "add", after making some basic settings.  
  **NOTICE: Let "Detect field types" in "Record and Fields Options" unselect.**
4. In QGIS, save the csv layer as the gpkg file by "Right clicking the csv layer->Export->Save Features As...".
5. In QGIS | Save Vector Layer as..., select GeoPackage as file format in "Format" befor Click "OK".
6. In QGIS, select the new gpkg layer and you can set the boundary conditions.  
  *Selected nodes -> Toggle Editing -> Modify the Attributes of All Selected Features Simultaneously*  
  *Normaly, field_5 means boundary type,*  
           *field_6 means boundary head, (If your head of boundary condition isn`t zero, remember to set this field)*  
           *field_7 means boundary flow,*  
           *field_8 means boundary group.*  
  *Click OK -> Save Layer Edits -> Toggle Editing.*
7. In QGIS, save the gpkg layer as the new csv file by "Right clicking the gpkg layer->Export->Save Features As...".
8. In QGIS | Save Vector Layer as..., select Comma Separated Value [CSV] as file format in "Format".  
**NOTICE: Let "fid" in "Select fields to export and ..." unselect** befor clicking "OK".


----
## Step2: Modify the mff file

* (If you change fractures number, you do not need to redo step 1 but step 2.)
1. Click "open CSV from QGIS" button and select a csv file which was generated in step 1-8.
2. Click "modify mff from Fracman" button and select the mff file which was created by Fracman.  
  *This step will generate a modified mff file which is named ".mff", and the old one will rename as ".old".*

