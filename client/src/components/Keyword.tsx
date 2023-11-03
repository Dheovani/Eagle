import { useState, useEffect } from "react";
import { GiBroom } from "react-icons/gi";
import { GetMethod } from "../utils/RestMethods";
import { Tooltip } from "../utils/Tooltip";
import { History, KEYWORD } from "./History";

export interface Keyword {
	keyword: string;
	id?: number;
	date?: Date;
}

export const KeywordInput = (props: any): JSX.Element => {
	const [selected, setSelected] = useState(false);
	const [keyword, setKeyword] = useState<Keyword[]>([]);

	const updateHistory = (): void => {
		GetMethod("http://localhost:8080/api/v1/Keyword", (status: number, response: any) => {
			if (status === 200) setKeyword(response);
		});
	};

	useEffect(() => {
		updateHistory();
	}, [selected]);

	const renderHistory = (): JSX.Element => {
		if (!keyword?.length) return <div></div>;

		return (
			<History
				items={keyword}
				endpoint={KEYWORD}
				updateDefaultValue={props.updateDefaultValue}
			/>
		);
	};

	const info = "Este campo contém as palavras que devem ser buscadas.";

	return (
		<>
			<h2>
				Pesquisa
				{<Tooltip info={info} />}
			</h2>
			<div className="input-content">
				<input
					className="fields"
					type="text"
					name="keyword"
					id="keyword"
					value={props.defaultValue}
					placeholder={selected ? "" : "Digite aqui as palavras-chave"}
					disabled={props.disable}
					onFocus={() => setSelected(true)}
					onBlur={() => setSelected(false)}
					onChange={(e) => {
						const keyword = {
							keyword: e.target.value,
							date: new Date(),
						};
						props.updateDefaultValue(keyword);
					}}
				/>

				<button
					disabled={props.disable}
					className="input-buttons"
					onClick={() => props.updateDefaultValue({ keyword: "" })}>
					<GiBroom />
				</button>
			</div>

			{selected && renderHistory()}
		</>
	);
};
