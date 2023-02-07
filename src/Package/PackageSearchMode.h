//
// Created by ebeuque on 07/02/23.
//

#ifndef STARDEPS_PACKAGESEARCHMODE_H
#define STARDEPS_PACKAGESEARCHMODE_H

#include <QString>

class PackageSearchMode {
public:
	enum SearchMode {
		Unknown = 0x00,
		Environment = 0x01,
		System = 0x02,
		Custom = 0x04,
		All = 0xFF,

		Default = Environment
	};

	PackageSearchMode();
	PackageSearchMode(SearchMode iSearchMode);
	virtual ~PackageSearchMode();

	static PackageSearchMode fromString(const QString& szSearchMode);
	void setFromString(const QString& szSearchMode);
	QString toString() const;

	bool operator==(const PackageSearchMode& other) const;
	bool operator==(const PackageSearchMode::SearchMode& iSearchMode) const;
	PackageSearchMode& operator=(const PackageSearchMode& other);
	PackageSearchMode& operator=(const PackageSearchMode::SearchMode& iSearchMode);

private:
	SearchMode m_iMode;
};


#endif //STARDEPS_PACKAGESEARCHMODE_H
