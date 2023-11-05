import { useState } from "react";
import { Panel, Line } from "./components/Panel";
import { PostMethod } from "./utils/RestMethods";
import { Path, PathInput } from "./components/Path";
import { Filter, FilterInput } from "./components/Filter";
import { Keyword, KeywordInput } from "./components/Keyword";
import { ToastContainer } from "react-toastify";
import Eagle from "./assets/logo.png";
import "./styles/App.css";
import "react-toastify/dist/ReactToastify.css";

const Logo = (): JSX.Element => {
	return (
		<div className="logo">
			<img src={Eagle} alt="logo" />
		</div>
	);
};

export const App = (): JSX.Element => {
	const [path, setPath] = useState<Path>({ path: "" });
	const [filter, setFilter] = useState<Filter>({ filter: "" });
	const [keyword, setKeyword] = useState<Keyword>({ keyword: "" });
	const [subFolders, setSubFolders] = useState(true);
	const [ignoreCase, setIgnoreCase] = useState(true);

	const submit = (): void => {
		if (path?.path && path?.id == undefined) {
			PostMethod(
				"http://localhost:8080/api/v1/Path",
				JSON.stringify(path),
				(status: number, response: any) => {
					if (status == 200)
						setPath(response);
				}
			);
		}

		if (filter?.filter && filter?.id == undefined) {
			PostMethod(
				"http://localhost:8080/api/v1/Filter",
				JSON.stringify(filter),
				(status: number, response: any) => {
					if (status == 200)
						setPath(response);
				}
			);
		}

		if (keyword?.keyword && keyword?.id == undefined) {
			PostMethod(
				"http://localhost:8080/api/v1/Keyword",
				JSON.stringify(keyword),
				(status: number, response: any) => {
					if (status == 200)
						setPath(response);
				}
			);
		}
	};

	const cleanAll = (): void => {
		setPath({ path: "" });
		setFilter({ filter: "" });
		setKeyword({ keyword: "" });
	};

	const params = {
		path: path,
		filter: filter,
		keyword: keyword,
		subFolders: subFolders,
		ignoreCase: !ignoreCase
	};

	return (
		<div className="App">
			<ToastContainer />
			<Logo />

			<div className="inputs">
				<KeywordInput
					defaultValue={keyword?.keyword}
					updateDefaultValue={setKeyword}
				/>

				<FilterInput
					defaultValue={filter?.filter}
					updateDefaultValue={setFilter}
					checked={ignoreCase}
					setIgnoreCase={setIgnoreCase}
				/>

				<PathInput
					defaultValue={path?.path}
					updateDefaultValue={setPath}
					checked={subFolders}
					setSubFolders={setSubFolders}
				/>
			</div>

			<Panel
				submit={submit}
				cleanAll={cleanAll}
				params={params}
			/>
		</div>
	);
};
