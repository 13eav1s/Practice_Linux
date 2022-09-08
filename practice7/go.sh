#!/bin/bash
mkdir "apps"
bash build_apps.sh
mkdir "data"
bash update_data.sh
mkdir "prep_data"
python3 make_preproc.py
mkdir "errorgraph_data"
mkdir "post_prep_lingraph_data"
python3 make_postproc.py
