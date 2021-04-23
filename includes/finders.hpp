#pragma once

#include <list>
#include <vector>
#include <string>
#include "../external_includes/units.hpp"


/* 
	Base class for finder. You can extend it with own addresses for base nodes or new nodes
 */
class FinderBase {
protected:

	class NodePath {
	private:
		// path of xml nodes' names
		std::list<std::string> nodesNames;

	public:
		NodePath(std::initializer_list<std::string> init_list) : nodesNames(init_list) {}

		std::string GetValueFromNode(Units::Unit* rootUnit) {
			if (rootUnit->GetName() != nodesNames.front()) {
				return " ";
			}

			auto iterator = nodesNames.begin();
			iterator++;
			for (; iterator != nodesNames.end(); iterator++) {
				rootUnit = rootUnit->GetChild(*iterator);
				if (rootUnit == nullptr) return " ";
			}

			std::string rtnValue;
			rootUnit->GetValue(rtnValue);

			return rtnValue;
		}

	};

	// base nodes
	NodePath plotNumber;
	NodePath plotSize;
	NodePath landNumber;
	NodePath district1Number;
	NodePath district2Number;
	NodePath gemarkungNumber;

public:
	FinderBase(
		std::initializer_list<std::string> _plotNumber,
		std::initializer_list<std::string> _plotSize,
		std::initializer_list<std::string> _landNumber,
		std::initializer_list<std::string> _district1Number,
		std::initializer_list<std::string> _district2Number,
		std::initializer_list<std::string> _gemarkungNumber
	) : plotNumber(_plotNumber), plotSize(_plotSize), landNumber(_landNumber), 
		district1Number(_district1Number), district2Number(_district2Number), gemarkungNumber(_gemarkungNumber) {}

	std::vector<std::string> FindValues(Units::Unit* rootUnit) {
		std::vector<std::string> values;
		values.push_back(plotNumber.GetValueFromNode(rootUnit));
		values.push_back(plotSize.GetValueFromNode(rootUnit));
		values.push_back(landNumber.GetValueFromNode(rootUnit));
		values.push_back(district1Number.GetValueFromNode(rootUnit));
		values.push_back(district2Number.GetValueFromNode(rootUnit));
		values.push_back(gemarkungNumber.GetValueFromNode(rootUnit));

		return values;
	}
};

class FinderAAA : public FinderBase {
public:
	FinderAAA() : FinderBase(
		{"wfs:FeatureCollection", "wfs:member", "Flurstueck", "flstkennz"},
		{"wfs:FeatureCollection", "wfs:member", "Flurstueck", "flaeche"},
		{"wfs:FeatureCollection", "wfs:member", "Flurstueck", "landschl"},
		{"wfs:FeatureCollection", "wfs:member", "Flurstueck", "kreisschl"},
		{"wfs:FeatureCollection", "wfs:member", "Flurstueck", "gmdschl"},
		{"wfs:FeatureCollection", "wfs:member", "Flurstueck", "gemaschl"}
	) {}
};

class FinderNAS : public FinderBase {
public:
	FinderNAS() : FinderBase(
		{"AX_Bestandsdatenauszug", "enthaelt", "wfs:FeatureCollection", "gml:featureMember", "AX_Flurstueck", "flurstueckskennzeichen"},
		{"AX_Bestandsdatenauszug", "enthaelt", "wfs:FeatureCollection", "gml:featureMember", "AX_Flurstueck", "amtlicheFlaeche"},
		{"AX_Bestandsdatenauszug", "enthaelt", "wfs:FeatureCollection", "gml:featureMember", "AX_Flurstueck", "gemeindezugehoerigkeit", "AX_Gemeindekennzeichen", "land"},
		{"AX_Bestandsdatenauszug", "enthaelt", "wfs:FeatureCollection", "gml:featureMember", "AX_Flurstueck", "gemeindezugehoerigkeit", "AX_Gemeindekennzeichen", "kreis"},
		{"AX_Bestandsdatenauszug", "enthaelt", "wfs:FeatureCollection", "gml:featureMember", "AX_Flurstueck", "gemeindezugehoerigkeit", "AX_Gemeindekennzeichen", "gemeinde"},
		{"AX_Bestandsdatenauszug", "enthaelt", "wfs:FeatureCollection", "gml:featureMember", "AX_Flurstueck", "gemarkung", "AX_Gemarkung_Schluessel", "gemarkungsnummer"}
	) {}
};

// to create own Finder, create new derived class of FinderBase, input paths for base nodes in constructor and, optionally, declare other NodePaths (overriding constructor and FindValues is necessary)